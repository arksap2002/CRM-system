#include "useCases.h"

namespace useCases {

    UseCase(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

//    UseCaseAddManager::UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
//        : managerRepository(std::move(managerRepository_)) {
//    }

    void UseCaseAddManager::addManager(const people::Manager &manager) const {
        try {
            managerRepository->addManager(manager);
        } catch (const repositories::FolderExists &folderExists) {
            std::cerr << repositories::FolderExists::get_name() << "\n";
            throw folderExists;
        }
    }

//    UseCaseGetManager::UseCaseGetManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
//        : managerRepository(std::move(managerRepository_)) {
//    }

    void UseCaseGetManager::getManager(people::Manager &input_manager, const std::string &input_email) const {
        managerRepository->getManager(input_manager, input_email);
    }

//    UseCaseInCorrectPassword::UseCaseInCorrectPassword(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
//        : managerRepository(std::move(managerRepository_)) {
//    }

    bool UseCaseInCorrectPassword::isCorrectPassword(const std::string &input_email, const std::string &input_password) const {
        try {
            return managerRepository->is_correct_password(input_email, input_password);
        } catch (const repositories::FolderNotExists &folderNotExists) {
            std::cerr << repositories::FolderNotExists::get_name() << "\n";
            throw folderNotExists;
        }
    }
}// namespace useCases