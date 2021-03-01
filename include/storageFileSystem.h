#ifndef CRM_SYSTEM_STORAGEFILESYSTEM_H
#define CRM_SYSTEM_STORAGEFILESYSTEM_H
#include "storage.h"

namespace repositories {

    struct FolderExists : std::exception {
        static std::string get_name();
        FolderExists() = default;
    };

    struct FolderNotExists : std::exception {
        static std::string get_name();
        FolderNotExists() = default;
    };

    struct ManagerFileSystem : ManagerRepository {
    private:
        void load_clients(people::Manager &manager) const override;
    public:
        ManagerFileSystem();
        void addManager(const people::Manager &manager) const override;
        void getManager(people::Manager &input_manager, const std::string &input_email) const override;
        [[nodiscard]] bool is_correct_password(const std::string &input_email, const std::string &input_password) const override;
        ~ManagerFileSystem() override = default;
    };

}// namespace repositories

#endif//CRM_SYSTEM_STORAGEFILESYSTEM_H
