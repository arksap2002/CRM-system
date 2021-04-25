#ifndef CRM_SYSTEM_STORAGEDATABASE_H
#define CRM_SYSTEM_STORAGEDATABASE_H

namespace repositories {

    struct ManagerException : runtime_error{
        ManagerException(const std::string& arg);
    };

    struct ClientException : runtime_error{
        ClientException(const std::string& arg);
    };

    struct ManagerDataBase : ManagerRepository {
    private:
        std::unique_ptr<Greeter::Stub> stub_;
    public:
        ManagerDataBase();
        void addManager(const people::Manager &manager) const override;
        void getManager(people::Manager &inputManager, const std::string &inputEmail) const override;
        [[nodiscard]] bool isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const override;
        std::string managerInfo(people::Manager &manager) const override;
        ~ManagerFileSystem() override = default;
    };

    struct ClientDataBase : ClientRepository {
    private:
        std::unique_ptr<Greeter::Stub> stub_;
    public:
        ClientDataBase();
        void addClient(const people::Client &client, const std::string &managerEmail) const override;
        void deleteClient(const std::string &clientEmail, const std::string &managerEmail) const override;
        void updateAllClients(const people::Manager &manager) const override;
        [[nodiscard]] std::string clientInfo(const people::Client &client) const override;
        [[nodiscard]] std::vector<std::string> getDealProcess(const people::Client &client) const override;
        ~ClientFileSystem() override = default;
    };
}// namespace repositories

#endif//CRM_SYSTEM_STORAGEDATABASE_H
