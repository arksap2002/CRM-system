#ifndef CRM_SYSTEM_USECASES_H
#define CRM_SYSTEM_USECASES_H
#include "storage.h"
#include "storageFileSystem.h"

#include <memory>

namespace useCases {
    class UseCaseAddManager {
        std::unique_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_);
        void addManager(const people::Manager &manager);
    };

    class UseCaseGetManager {
        void getManager();
    };

    //class UseCaseFindManager { //?????
    //
    //};

    class UseCaseIsCorrectPassword {
        void isCorrectPassword();
    };

    class UseCaseAddClient {
        void addClient();
    };

    class UseCaseDeleteClient {
        void deleteClient();
    };
}// namespace useCases
#endif//CRM_SYSTEM_USECASES_H
