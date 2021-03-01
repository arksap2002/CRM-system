#ifndef CRM_SYSTEM_STORAGEFILESYSTEM_H
#define CRM_SYSTEM_STORAGEFILESYSTEM_H
#include "storage.h"

namespace repositories {

    class FolderNotExists : std::exception {
    public:
        static std::string get_name();
        FolderNotExists() = default;
    };

    class ManagerFileSystem : ManagerRepository {
        void preparatoryCheck() const override;//check_resources_tree
        void addManager(const people::Manager &manager) const override;
        [[nodiscard]] bool is_correct_password(const std::string &email, const std::string &inputPassword) const override;
    };

}// namespace repositories

#endif//CRM_SYSTEM_STORAGEFILESYSTEM_H
