#ifndef CRM_SYSTEM_STORAGEFILESYSTEM_H
#define CRM_SYSTEM_STORAGEFILESYSTEM_H
#include "storage.h"

namespace repositories {

    struct FolderExists : std::exception {
        static std::string get_name();
        FolderExists() = default;
    };

    struct ManagerFileSystem : ManagerRepository {
        ManagerFileSystem();
        void addManager(const people::Manager &manager) const override;
        ~ManagerFileSystem() override = default;
    };

}// namespace repositories

#endif//CRM_SYSTEM_STORAGEFILESYSTEM_H
