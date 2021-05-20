#include "useCases_server.h"

namespace useCasesServer{
    UseCaseServerAddManager::UseCaseServerAddManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_)
                    : database(database_){}

    int UseCaseServerAddManager::addManager(const AddManagerRequest *request) const{
        int id = 0;
        try{
            id = database->addManager(request);
        }
        catch(...){
            std::cout << "Exception" << std::endl;
        }
        return id;
    }
}