#include "useCases_server.h"
#include <exception>

namespace useCasesServer{
    UseCaseServerAddManager::UseCaseServerAddManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    UseCaseServerGetManager::UseCaseServerGetManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    UseCaseServerIsCorrectPassword::UseCaseServerIsCorrectPassword(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    UseCaseServerAddClient::UseCaseServerAddClient(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    UseCaseServerDeleteClient::UseCaseServerDeleteClient(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    UseCaseServerUpdateAllClients::UseCaseServerUpdateAllClients(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}


    int UseCaseServerAddManager::addManager(const AddManagerRequest *request, AddManagerReply *reply) const{
        int id = 0;
        try{
            id = database->addManager(request, reply);
            if (reply->fail()){
                std::cout << "Can not add manager\n";
            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerGetManager::getManager(const GetManagerRequest *request, GetManagerReply *reply) const {
        int id = 0;
        try{
            id = database->getManager(request, reply);
            if (reply->fail()){
                std::cout << "Can not get manager\n";
            }
//            for (int i = 0; i < reply->inputmanager().num_clients(); ++i){
//                reply->inputmanager().listclients(i).dealprocess(0).set_title("Connection with client");
//                reply->inputmanager().listclients(i).dealprocess(1).set_title("Concluding the contract");
//                reply->inputmanager().listclients(i).dealprocess(2).set_title("Deal is completed");
//            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerIsCorrectPassword::isCorrectPassword(const IsCorrectPasswordRequest *request, IsCorrectPasswordReply *reply) const{
        int id = 0;
        try{
            id = database->isCorrectPassword(request, reply);
            if (reply->fail()){
                std::cout << "Can not check password\n";
            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerAddClient::addClient(const AddClientRequest *request, AddClientReply *reply) const {
        int id = 0;
        try{
            id = database->addClient(request, reply);
            if (reply->fail_table() || reply->fail_client()){
                std::cout << "Can not add client\n";
            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerDeleteClient::deleteClient(const DeleteClientRequest *request, DeleteClientReply *reply) const {
        int id = 0;
        try{
            id = database->deleteClient(request, reply);
            if (reply->fail_table() || reply->fail_client()){
                std::cout << "Can not delete client\n";
            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerUpdateAllClients::updateAllClients(const UpdateAllClientsRequest *request, UpdateAllClientsReply *reply) const{
        int id = 0;
        try{
            id = database->updateAllClients(request, reply);
            if (reply->fail()){
                std::cout << "Can not update all clients\n";
            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }
}