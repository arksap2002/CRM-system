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
//            std::cout << "UseCase start getManager\n";
            id = database->getManager(request, reply);
//            std::cout << "UseCase finish getManager\n";
//            if (reply->fail()){
//                std::cout << "Can not get manager\n";
//            }
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
//            std::cout << "UseCase start isCorrectPassword\n";
            id = database->isCorrectPassword(request, reply);
//            std::cout << "UseCase finish isCorrectPassword\n";
//            if (reply->fail()){
//                std::cout << "Can not check password\n";
//            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerAddClient::addClient(const AddClientRequest *request, AddClientReply *reply) const {
        int id = 0;
        try{
//            std::cout << "UseCase start addClient\n";
            id = database->addClient(request, reply);
//            std::cout << "UseCase finish addClient\n";
//            if (reply->fail()){
//                std::cout << "Can not add client\n";
//            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerDeleteClient::deleteClient(const DeleteClientRequest *request, DeleteClientReply *reply) const {
        int id = 0;
        try{
//            std::cout << "UseCase start deleteClient\n";
            id = database->deleteClient(request, reply);
//            std::cout << "UseCase start deleteClient\n";
//            if (reply->fail()){
//                std::cout << "Can not delete client\n";
//            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }

    int UseCaseServerUpdateAllClients::updateAllClients(const UpdateAllClientsRequest *request, UpdateAllClientsReply *reply) const{
        int id = 0;
        try{
//            std::cout << "UseCase start updateAllClients\n";
            id = database->updateAllClients(request, reply);
//            std::cout << "UseCase finish updateAllClient\n";
//            if (reply->fail()){
//                std::cout << "Can not update all clients\n";
//            }
        }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }
}