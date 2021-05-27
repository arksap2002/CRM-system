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
//                std::cout << "Alarm!" << std::endl;
//                std::cout << "Manager already exists" << std::endl;
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
//            std::string clients_table = make_clients_table(request->manager().email());
//            stmt->execute("CREATE TABLE " + clients_table + "("
//                 "    id int NOT NULL AUTO_INCREMENT,"
//                 "    email varchar(1000) NOT NULL,"
//                 "    name varchar(1000) NOT NULL,"
//                 "    phone varchar(1000) NOT NULL,"
//                 "    dealProduct varchar(1000) NOT NULL,"
//                 "    dealProcess int NOT NULL,"
//                 "    PRIMARY KEY (id)"
//                 ")"
//            );
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
//            std::cout << "Can not add manager" << std::endl;
//            show_error(__FILE__, __FUNCTION__, __LINE__, e);
//            return -1;
            throw dataBaseError(__FILE__, __FUNCTION__, e);
        }
    }

    int CrmSystemDataBase::getManager(const GetManagerRequest *request, GetManagerReply *reply){
        try{
            sql::Statement *stmt = con->createStatement();
//            std::cout << ("SELECT * FROM Managers WHERE email='" + request->inputemail() + "'\n");
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->inputemail() + "'");
            if (!res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Manager is not exists");
            }
            ManagerGRPC* managerGrpc = new ManagerGRPC();
            managerGrpc->set_email(res->getString(1));
            managerGrpc->set_password(res->getString(2));
            managerGrpc->set_name(res->getString(3));
            managerGrpc->set_phone(res->getString(4));
            delete res;
//            std::string clients_table = make_clients_table(request->inputemail());
            std::cout << ("SELECT count(*) FROM Clients WHERE manager_email='" + request->inputemail() +"'\n");
//            res = stmt->executeQuery("SELECT count(*) FROM " + clients_table);
            res = stmt->executeQuery("SELECT count(*) FROM Clients WHERE manager_email='" + request->inputemail() +"'");
            res->next(); managerGrpc->set_num_clients(res->getInt(1)); delete res;
//            std::cout << ("SELECT * FROM " + clients_table + "\n");
            std::cout << ("SELECT * FROM Clients WHERE manager_email='" + request->inputemail() +"'\n");
            res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->inputemail() + "'");
            while(res->next()){
                std::cout << "make clientGrpc\n";
                ClientGRPC* clientGrpc = managerGrpc->add_listclients();
                std::cout << "make email\n";
                clientGrpc->set_email(res->getString(1));
                std::cout << "make name\n";
                clientGrpc->set_name(res->getString(2));
                std::cout << "make phone\n";
                clientGrpc->set_phone(res->getString(3));
                std::cout << "make dealproduct\n";
                clientGrpc->set_dealproduct(res->getString(4));
                std::cout << "make dealProcess\n";
                for (int i = 0; i < 3; ++i){
                    DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                    std::cout << (res->getInt(5) & (1 << i)) << " ";
                    dealProcessGrpc->set_completed(res->getInt(5) & (1 << i));
                }
                std::cout << "\n";
            }
            std::cout << "set manager\n";
            reply->set_allocated_inputmanager(managerGrpc);
            std::cout << "set_fail\n";
            reply->set_fail(false);
            delete res;
//            std::cout << ("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'\n");
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
//            std::cout << ("SELECT password FROM Managers WHERE email='" + request->inputemail() + "'\n");
            sql::ResultSet *res = stmt->executeQuery("SELECT password FROM Managers WHERE email='" + request->inputemail() + "'");
            if(!res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Can not find Manager");
            }
            reply->set_fail(false);
            reply->set_find(res->getString(1) == request->inputpassword());
            delete res;
//            std::cout << ("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'\n");
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->inputemail() + "'");
//            std::cout << "selected...\n";
            res->next();
//            std::cout << res->getInt(1) << "\n";
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
//            std::string clients_table = make_clients_table(request->manageremail());
//            std::cout << "SHOW TABLES LIKE '" << clients_table << "'\n";
//            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE '" + clients_table + "'");
//            if(!res->next()){
//                reply->set_fail_table(true);
//                throw std::runtime_error("Can not find table");
//            }
//            reply->set_fail_table(false);
//            delete res;
//            std::cout << "SELECT * FROM " << clients_table << " WHERE email='" << request->client().email() << "'\n";
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->manageremail()
                                                     + "' AND email='" + request->client().email() + "'");
            if (res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Client already exists");
            }
            reply->set_fail(false);
            delete res;
            int dealProcess = 0;
            for (int j = 0; j < 3; ++j){
                dealProcess |= request->client().dealprocess(j).completed() << j;
            }
            /*std::cout << ("INSERT INTO " + clients_table + "(email, name, phone, dealProduct, dealProcess) VALUES('"
                          + request->client().email() + "', '"
                          + request->client().name() + "', '"
                          + request->client().phone() + "', '"
                          + request->client().dealproduct() + "', "
                          + std::to_string(dealProcess) + ")\n");*/
            stmt->execute("INSERT INTO Clients(manager_email, email, name, phone, dealProduct, dealProcess) VALUES('"
                          + request->manageremail() + "', '"
                          + request->client().email() + "', '"
                          + request->client().name() + "', '"
                          + request->client().phone() + "', '"
                          + request->client().dealproduct() + "', "
                          + std::to_string(dealProcess) + ")"
            );
//            std::cout << ("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'\n");
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email='" + request->manageremail() + "'");
            res->next(); reply->set_managerid(res->getInt(1));
            delete res;
//            std::cout << ("SELECT id FROM " + clients_table + " WHERE email='" + request->client().email() + "'\n");
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
//            std::string clients_table = make_clients_table(request->manageremail());
//            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE '" + clients_table + "'");
//            if(!res->next()){
//                reply->set_fail_table(true);
//                throw std::runtime_error("Can not find table");
//            }
//            reply->set_fail_table(false);
//            delete res;
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='" + request->manageremail()
                                                    + "' AND email='" + request->clientemail() + "'");
            if (!res->next()){
                reply->set_fail(true);
                throw std::runtime_error("Client is not exists");
            }
            reply->set_fail(false);
            delete res;
            res = stmt->executeQuery("SELECT id FROM Clients WHERE manager_email='" + request->manageremail() +
                                     "' AND email='" + request->clientemail() + "'");
            res->next(); reply->set_clientid(res->getInt(1));
            delete res;
            stmt->execute("DELETE FROM Clients WHERE manager_email='" + request->manageremail() +
                          "' AND email='" + request->clientemail()) + "'";
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
//            std::string clients_table = make_clients_table(request->manageremail());
//            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE '" + clients_table + "'");
//            if(!res->next()){
//                reply->set_fail(true);
//                throw std::runtime_error("Can not find table");
//            }
//            reply->set_fail(false);
//            delete res;
            sql::ResultSet *res = stmt->executeQuery("SELECT count(*) FROM Clients WHERE manager_email='"
                                                     + request->manageremail() +"'");
            res->next(); reply->set_count_clients(res->getInt(1));
            delete res;
            res = stmt->executeQuery("SELECT * FROM Clients WHERE manager_email='"
                                     + request->manageremail() +"'");
            while(res->next()){
                ClientGRPC *clientGrpc = reply->add_listclients();
                clientGrpc->set_email(res->getString(1));
                clientGrpc->set_name(res->getString(2));
                clientGrpc->set_phone(res->getString(3));
                clientGrpc->set_dealproduct(res->getString(4));
                for (int i = 0; i < 3; ++i){
                    DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                    dealProcessGrpc->set_completed(res->getInt(5) & (1 << i));
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