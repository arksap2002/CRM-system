#include "storageDataBase.h"
#include <typeinfo>
#include <boost/core/demangle.hpp>
namespace storageSQL{

    using namespace crm_system;

    dataBaseError::dataBaseError(const std::string& file, const std::string& function, const sql::SQLException& e) :
        std::runtime_error("# ERR: SQLException in " + file + "(" + function + ")\n"
                      "# ERR: " + e.what() + " (MySQL error code: " + std::to_string(e.getErrorCode())
                      + ", SQLState: " + e.getSQLState() + " )") {}

    CrmSystemDataBase::CrmSystemDataBase() {
        try{
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "CRM_system_user", "ZW5FAQ");
            con->setSchema("CRM_system_storage");
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE 'Managers'");
            if (!(res->next())){
                stmt->execute("CREATE TABLE Managers("
                              "    id int NOT NULL AUTO_INCREMENT,"
                              "    email varchar(1000) NOT NULL,"
                              "    password varchar(1000) NOT NULL,"
                              "    name varchar(1000) NOT NULL,"
                              "    phone varchar(1000) NOT NULL,"
                              "    PRIMARY KEY (id)"
                              ")");
            } delete res;
            res = stmt->executeQuery("SHOW TABLES LIKE 'Clients'");
            if (!(res->next())){
                stmt->execute("CREATE TABLE Clients("
                              "    id int NOT NULL AUTO_INCREMENT,"
                              "    manager_email varchar(1000) NOT NULL,"
                              "    email varchar(1000) NOT NULL,"
                              "    name varchar(1000) NOT NULL,"
                              "    phone varchar(1000) NOT NULL,"
                              "    dealProduct varchar(1000) NOT NULL,"
                              "    dealProcess int NOT NULL,"
                              "    PRIMARY KEY (id)"
                              ")");
            } delete res;
            delete stmt;
        }
        catch (const sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::addManager(const AddManagerRequest *request, AddManagerReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->manager().email() + "'");
            if (res->next()){
                delete res;
                delete stmt;
                reply->set_fail(true);
                return -1;
            }
            stmt->execute("INSERT INTO Managers(email, password, name, phone) VALUES('"
                 + request->manager().email() + "', '"
                 + request->manager().password() + "', '"
                 + request->manager().name() + "', '"
                 + request->manager().phone()
                 + "')"
            );
            delete res;
            int dealProcess = 0;
            for (int i = 0; i < request->manager().num_clients(); ++i){
                for (int j = 0; j < 3; ++j){
                    dealProcess |= request->manager().listclients(i).dealprocess(j).completed() << j;
                }
                stmt->execute("INSERT INTO Clients(manager_email, email, name, phone, dealProduct, dealProcess) VALUES('"
                    + request->manager().email() + "', "
                    + request->manager().listclients(i).email() + "', '"
                    + request->manager().listclients(i).name() + "', '"
                    + request->manager().listclients(i).phone() + "', '"
                    + request->manager().listclients(i).dealproduct() + "', "
                    + std::to_string(dealProcess) + ")"
                );
                dealProcess = 0;
            }
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manager().email() + "'");
            res->next();
            reply->set_managerid(res->getInt(1));
            reply->set_fail(false);
            delete res;
            delete stmt;
            return reply->managerid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::getManager(const GetManagerRequest *request, GetManagerReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->inputemail() + "'");
            if (!res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Manager is not exists");
            }
            ManagerGRPC* managerGrpc = new ManagerGRPC();
            managerGrpc->set_email(res->getString(2));
            managerGrpc->set_password(res->getString(3));
            managerGrpc->set_name(res->getString(4));
            managerGrpc->set_phone(res->getString(5));
            delete res;
            res = stmt->executeQuery("SELECT count(*) FROM Clients WHERE manager_email='" + request->inputemail() +"'");
            res->next(); managerGrpc->set_num_clients(res->getInt(1)); delete res;
            res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->inputemail() + "'");
            while(res->next()){
                ClientGRPC* clientGrpc = managerGrpc->add_listclients();
                clientGrpc->set_email(res->getString(3));
                clientGrpc->set_name(res->getString(4));
                clientGrpc->set_phone(res->getString(5));
                clientGrpc->set_dealproduct(res->getString(6));
                for (int i = 0; i < 3; ++i){
                    DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                    dealProcessGrpc->set_completed(res->getInt(7) & (1 << i));
                }
            }
            reply->set_allocated_inputmanager(managerGrpc);
            reply->set_fail(false);
            delete res;
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'");
            res->next();
            int id = res->getInt(1);
            delete res;
            delete stmt;
            return id;
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::isCorrectPassword(const IsCorrectPasswordRequest *request, IsCorrectPasswordReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT password FROM Managers WHERE email='" + request->inputemail() + "'");
            if(!res->next()){
                reply->set_fail(true);
                return -1;
            }
            reply->set_fail(false);
            reply->set_find(res->getString(1) == request->inputpassword());
            delete res;
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'");
            res->next();
            int id = res->getInt(1);
            delete res;
            delete stmt;
            return id;
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::addClient(const AddClientRequest *request, AddClientReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->manageremail()
                                                     + "' AND email='" + request->client().email() + "'");
            if (res->next()){
                reply->set_fail(true);
                return -1;
            }
            reply->set_fail(false);
            delete res;
            int dealProcess = 0;
            for (int j = 0; j < 3; ++j){
                dealProcess |= request->client().dealprocess(j).completed() << j;
            }
            stmt->execute("INSERT INTO Clients(manager_email, email, name, phone, dealProduct, dealProcess) VALUES('"
                          + request->manageremail() + "', '"
                          + request->client().email() + "', '"
                          + request->client().name() + "', '"
                          + request->client().phone() + "', '"
                          + request->client().dealproduct() + "', "
                          + std::to_string(dealProcess) + ")"
            );
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            delete res;
            res = stmt->executeQuery("SELECT id FROM Clients WHERE manager_email='" + request->manageremail()
                                     + "' AND email='" + request->client().email() + "'");
            res->next(); reply->set_clientid(res->getInt(1));
            delete res;
            delete stmt;
            return reply->clientid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::deleteClient(const DeleteClientRequest *request, DeleteClientReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->manageremail()
                                                    + "' AND email='" + request->clientemail() + "'");
            if (!res->next()){
                reply->set_fail(true);
                return -1;
            }
            reply->set_fail(false);
            delete res;
            res = stmt->executeQuery("SELECT id FROM Clients WHERE manager_email='" + request->manageremail() +
                                     "' AND email='" + request->clientemail() + "'");
            res->next(); reply->set_clientid(res->getInt(1));
            delete res;
            stmt->execute("DELETE FROM Clients WHERE manager_email='" + request->manageremail() +
                          "' AND email='" + request->clientemail() + "'");
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            delete res;
            delete stmt;
            return reply->clientid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::updateAllClients(const UpdateAllClientsRequest *request, UpdateAllClientsReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT count(*) FROM Clients WHERE manager_email='"
                                                     + request->manageremail() +"'");
            res->next(); reply->set_count_clients(res->getInt(1));
            delete res;
            res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='"
                                     + request->manageremail() +"'");
            while(res->next()){
                ClientGRPC *clientGrpc = reply->add_listclients();
                clientGrpc->set_email(res->getString(3));
                clientGrpc->set_name(res->getString(4));
                clientGrpc->set_phone(res->getString(5));
                clientGrpc->set_dealproduct(res->getString(6));
                for (int i = 0; i < 3; ++i){
                    DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                    dealProcessGrpc->set_completed(res->getInt(7) & (1 << i));
                }
            }
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            delete res;
            delete stmt;
            return reply->managerid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    CrmSystemDataBase::~CrmSystemDataBase(){
        delete con;
    }
}