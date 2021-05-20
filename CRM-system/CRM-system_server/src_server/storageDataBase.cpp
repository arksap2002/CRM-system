#include "storageDataBase.h"

namespace storageSQL{

    using namespace crm_system;

    void show_error(const std::string &file, const std::string &function, int line, sql::SQLException& e){
        std::cout << "# ERR: SQLException in " << file;
        std::cout << "(" << function << ") on line " << line << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    CrmSystemDataBase::CrmSystemDataBase() {
        try{
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "CRM_system_user", "ZW5FAQ");
            con->setSchema("CRM_system_storage");
            sql::Statement *stmt = con->createStatement();
//            std::cout << "???";
//            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES FROM CRM_system_storage LIKE Managers");
            sql::ResultSet *res = stmt->executeQuery("SHOW TABLES LIKE 'Managers'");
//            std::cout << "***";
            if (!(res->next())){
//                std::cout << "!!!";
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
        catch (sql::SQLException& e){
            std::cout << "Can not establish a connection" << std::endl;
            show_error(__FILE__, __FUNCTION__, __LINE__, e);
        }
    }

    int CrmSystemDataBase::addManager(const AddManagerRequest *request){
        try{
            sql::Statement *stmt = con->createStatement();
            std::cout << "***\n";
            std::cout << "SELECT * FROM Managers WHERE email=" << request->manager().email() << "'" << std::endl;
            sql::ResultSet *res = stmt->executeQuery("SELECT * FROM Managers WHERE email='" + request->manager().email() + "'");
            if (res->next()){
                std::cout << "Alarm!" << std::endl;
                std::cout << "Manager already exists" << std::endl;
                delete res;
                delete stmt;
                throw std::runtime_error("Manager already exists");
            }
            std::cout << "!!!";
            stmt->execute("INSERT INTO Managers(email, password, name, phone) VALUES("
                 + request->manager().email() + ", "
                 + request->manager().password() + ", "
                 + request->manager().name() + ", "
                 + request->manager().phone()
                 + ")"
            );
            std::cout << "???";
            std::string client_repository = "_" + request->manager().email();
            stmt->execute("CREATE TABLE " + client_repository + "("
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
                stmt->execute("INSERT INTO _" + client_repository + "(email, name, phone, dealProduct, dealProcess) VALUES("
                    + request->manager().listclients(i).email() + ", "
                    + request->manager().listclients(i).name() + ", "
                    + request->manager().listclients(i).phone() + ", "
                    + request->manager().listclients(i).dealproduct() + ", "
                    + std::to_string(dealProcess) + ")"
                );
            }
            delete res;
            res = stmt->executeQuery("SELECT id FROM Managers WHERE email=" + request->manager().email());
//            int returning_id = atoi(static_cast<std::string>(res->getInt(1)));
            int returning_id = res->getInt(1);
            delete res;
            delete stmt;
            return returning_id;
        }
        catch (sql::SQLException& e){
            std::cout << "Can not add manager" << std::endl;
            show_error(__FILE__, __FUNCTION__, __LINE__, e);
            return -1;
        }
    }

    CrmSystemDataBase::~CrmSystemDataBase(){
        delete con;
    }
}