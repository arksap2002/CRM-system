#include "useCases_server.h"
#include <exception>

namespace useCasesServer{
    UseCaseServerAddManager::UseCaseServerAddManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    int UseCaseServerAddManager::addManager(const AddManagerRequest *request, AddManagerReply *reply) const{
        int id = 0;
        try{ id = database->addManager(request, reply); }
        catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        return id;
    }
}