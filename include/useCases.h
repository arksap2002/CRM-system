#ifndef CRM_SYSTEM_USECASES_H
#define CRM_SYSTEM_USECASES_H
#include "storage.h"
#include "storageFileSystem.h"

#include <memory>

namespace useCases {
    struct UseCaseAddManager {
        std::unique_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_);
        void addManager(const people::Manager &manager);
    };
}// namespace useCases
#endif//CRM_SYSTEM_USECASES_H
