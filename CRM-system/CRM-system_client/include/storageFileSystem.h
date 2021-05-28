#ifndef CRM_SYSTEM_STORAGEFILESYSTEM_H
#define CRM_SYSTEM_STORAGEFILESYSTEM_H
#include "storage.h"

namespace repositories {

    struct FileExists : StorageException {
        FileExists();
    };

    struct FileNotExists : StorageException{
        FileNotExists();
    };

    struct ManagerFileSystem : ManagerRepository {
    private:
        static void load_clients(people::Manager &manager);

    public:
        ManagerFileSystem();
        void addManager(const people::Manager &manager) const override;
        void getManager(people::Manager &inputManager, const std::string &inputEmail) const override;
        [[nodiscard]] bool isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const override;
        std::string managerInfo(people::Manager &manager) const override;
        ~ManagerFileSystem() override = default;
    };

    struct ClientFileSystem : ClientRepository {
    public:
        ClientFileSystem();
        void addClient(const people::Client &client, const std::string &managerEmail) const override;
        void deleteClient(const std::string &clientEmail, const std::string &managerEmail) const override;
        void updateAllClients(people::Manager &manager) const override;
        [[nodiscard]] std::string clientInfo(const people::Client &client) const override;
        [[nodiscard]] std::vector<std::string> getDealProcess(const people::Client &client) const override;
        ~ClientFileSystem() override = default;
    };
}// namespace repositories

#endif//CRM_SYSTEM_STORAGEFILESYSTEM_H
