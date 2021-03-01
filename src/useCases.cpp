#include "useCases.h"
namespace useCases {

    UseCaseAddManager::UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

    void UseCaseAddManager::addManager(const people::Manager &manager) {
        try {
            managerRepository->addManager(manager);
        } catch (const repositories::FolderExists &folderExists) {
            std::cerr << repositories::FolderExists::get_name() << "\n";
            throw folderExists;
        }
    }

//    void UseCaseGetManager::getManager() {
//        //    TODO
//    }
//
//    void UseCaseIsCorrectPassword::isCorrectPassword() {
//        //    TODO
//    }
//
//    void UseCaseAddClient::addClient() {
//        //    TODO
//    }
//
//    void UseCaseDeleteClient::deleteClient() {
//        //    TODO
//    }
}// namespace useCases