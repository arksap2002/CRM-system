#ifndef CRM_SYSTEM_USECASES_H
#define CRM_SYSTEM_USECASES_H
#include "storage.h"
#include "storageFileSystem.h"
#include <memory>

namespace useCases {
    struct UseCase {
        std::unique_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCase(std::unique_ptr<repositories::ManagerRepository> managerRepository_);
    };

    struct UseCaseAddManager : UseCase {
        void addManager(const people::Manager &manager) const;
    };

    struct UseCaseGetManager : UseCase {
        void getManager(people::Manager &input_manager, const std::string &input_email) const;
    };

    struct UseCaseInCorrectPassword : UseCase {
        [[nodiscard]] bool isCorrectPassword(const std::string &input_email, const std::string &input_password) const;
    };

    struct UseCaseAddClient {
//        TODO Arkasha
    };
}// namespace useCases
#endif//CRM_SYSTEM_USECASES_H
