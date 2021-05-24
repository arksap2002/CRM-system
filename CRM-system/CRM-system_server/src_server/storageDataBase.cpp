#include "storageDataBase.h"
#include <typeinfo>
#include <boost/core/demangle.hpp>
namespace storageSQL{

    using namespace crm_system;

    dataBaseError::dataBaseError(const std::string& file, const std::string& function, const sql::SQLException& e) :
        std::runtime_error("# ERR: SQLException in " + file + "(" + function + ")\n"
                      "# ERR: " + e.what() + " (MySQL error code: " + std::to_string(e.getErrorCode())
                      + ", SQLState: " + e.getSQLState() + " )") {}

//    void show_error(const std::string &file, const std::string &function, int line, sql::SQLException& e){
//        std::cout << "# ERR: SQLException in " << file;
//        std::cout << "(" << function << ") on line " << line << std::endl;
//        std::cout << "# ERR: " << e.what();
//        std::cout << " (MySQL error code: " << e.getErrorCode();
//        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//    }

    std::string make_clients_table(const std::string& email){
        std::string clients_table = "Clients_" + email;
        for (char x : {'@', '.', ' '}){
            std::size_t found = clients_table.find(x);
            while (found != std::string::npos){
                clients_table[found] = 'a';
                found = clients_table.find(x);
            }
        }
        return clients_table;
    }

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
            }
        }
        catch (const sql::SQLException& e){
//            std::cout << "Can not establish a connection" << std::endl;
//            show_error(__FILE__, __FUNCTION__, __LINE__, e);
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::addManager(const AddManagerRequest *request, AddManagerReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->manager().email() + "'");
            if (res->next()){
                std::cout << "Alarm!" << std::endl;
                std::cout << "Manager already exists" << std::endl;
                delete res;
                delete stmt;
                reply->set_fail(true);
                throw std::runtime_error("Manager already exists");
            }
            stmt->execute("INSERT INTO Managers(email, password, name, phone) VALUES('"
                 + request->manager().email() + "', '"
                 + request->manager().password() + "', '"
                 + request->manager().name() + "', '"
                 + request->manager().phone()
                 + "')"
            );
            delete res;
            std::string clients_table = make_clients_table(request->manager().email());
            stmt->execute("CREATE TABLE " + clients_table + "("
                 "    id int NOT NULL AUTO_INCREMENT,"
                 "    email varchar(1000) NOT NULL,"
                 "    name varchar(1000) NOT NULL,"
                 "    phone varchar(1000) NOT NULL,"
                 "    dealProduct varchar(1000) NOT NULL,"
                 "    dealProcess int NOT NULL,"
                 "    PRIMARY KEY (id)"
                 ")"
            );
            int dealProcess = 0;
            for (int i = 0; i < request->manager().num_clients(); ++i){
                for (int j = 0; j < 3; ++j){
                    dealProcess |= request->manager().listclients(i).dealprocess(j).completed() << j;
                }
                stmt->execute("INSERT INTO " + clients_table + "(email, name, phone, dealProduct, dealProcess) VALUES('"
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
//            std::cout << "Can not add manager" << std::endl;
//            show_error(__FILE__, __FUNCTION__, __LINE__, e);
//            return -1;
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::getManager(const GetManagerRequest *request, GetManagerReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->inputemail() + "'");
            if (!res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Con not find manager");
            }
            ManagerGRPC* managerGrpc = new ManagerGRPC();
            managerGrpc->set_email(res->getString(1));
            managerGrpc->set_password(res->getString(2));
            managerGrpc->set_name(res->getString(3));
            managerGrpc->set_phone(res->getString(4));
            delete res;
            std::string clients_table = make_clients_table(request->inputemail());
            res = stmt->executeQuery("SELECT * FROM " + clients_table);
            while(res->next()){
                ClientGRPC* clientGrpc = managerGrpc->add_listclients();
                clientGrpc->set_email(res->getString(1));
                clientGrpc->set_name(res->getString(2));
                clientGrpc->set_phone(res->getString(3));
                clientGrpc->set_dealproduct(res->getString(4));
                for (int i = 0; i < 3; ++i){
                    DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                    dealProcessGrpc->set_completed(res->getInt(5) & (1 << i));
                }
            }
            reply->set_allocated_inputmanager(managerGrpc);
            reply->set_fail(false);
            delete res;
            delete stmt;
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'");
            res->next();
            return res->getInt(1);
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
                throw std::runtime_error("Can not find Manager");
            }
            reply->set_fail(true);
            reply->set_find(res->getString(1) == request->inputpassword());
            delete res;
            delete stmt;
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'");
            res->next();
            return res->getInt(1);
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::addClient(const AddClientRequest *request, AddClientReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            std::string clients_table = make_clients_table(request->manageremail());
            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE " + clients_table);
            if(!res->next()){
                reply->set_fail_table(true);
                throw std::runtime_error("Can not find table");
            }
            reply->set_fail_table(false);
            delete res;
            res = stmt->executeQuery("SELECT * FROM " + clients_table + " WHERE email='" + request->client().email() + "'");
            if (res->next()){
                reply->set_fail_client(true);
                throw std::runtime_error("Client already exists");
            }
            reply->set_fail_client(false);
            delete res;
            int dealProcess = 0;
            for (int j = 0; j < 3; ++j){
                dealProcess |= request->client().dealprocess(j).completed() << j;
            }
            stmt->execute("INSERT INTO " + clients_table + "(email, name, phone, dealProduct, dealProcess) VALUES('"
                          + request->client().email() + "', '"
                          + request->client().name() + "', '"
                          + request->client().phone() + "', '"
                          + request->client().dealproduct() + "', "
                          + std::to_string(dealProcess) + ")"
            );
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            res = stmt->executeQuery("SELECT id FROM " + clients_table + " WHERE email='" + request->client().email() + "'");
            res->next(); reply->set_clientid(res->getInt(1));
            return reply->clientid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::deleteClient(const DeleteClientRequest *request, DeleteClientReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
            std::string clients_table = make_clients_table(request->manageremail());
            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE " + clients_table);
            if(!res->next()){
                reply->set_fail_table(true);
                throw std::runtime_error("Can not find table");
            }
            reply->set_fail_table(false);
            delete res;
            res = stmt->executeQuery("SELECT * FROM " + clients_table + " WHERE email='" + request->clientemail() + "'");
            if (!res->next()){
                reply->set_fail_client(true);
                throw std::runtime_error("Client is not exists");
            }
            reply->set_fail_client(false);
            delete res;
            res = stmt->executeQuery("SELECT id FROM " + clients_table + " WHERE email='" + request->clientemail() + "'");
            res->next(); reply->set_clientid(res->getInt(1));
            stmt->execute("DELETE FROM " + clients_table + " WHERE email=" + request->clientemail());
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            return reply->clientid();
        }
        catch (sql::SQLException& e){
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::updateAllClients(const UpdateAllClientsRequest *request, UpdateAllClientsReply *reply){
        return 1;
    }

    CrmSystemDataBase::~CrmSystemDataBase(){
        delete con;
    }
}