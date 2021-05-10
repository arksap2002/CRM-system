#ifndef CRM_SYSTEM_STORAGEDATABASE_H
#define CRM_SYSTEM_STORAGEDATABASE_H
#include <iostream>
#include <memory>
#include <string>

#include <cstdio>
#include <vector>
#include "people.h"
#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"
#include <stdexcept>
#include "storage.h"

namespace repositories {

    using grpc::Channel;
    using grpc::ClientContext;
    using grpc::Status;

    using namespace crm_system;

    struct ManagerException : std::runtime_error{
        ManagerException(const std::string& arg);
    };

    struct ClientException : std::runtime_error{
        ClientException(const std::string& arg);
    };

    struct ManagerDataBase_client : ManagerRepository {
    private:
        std::unique_ptr<CRMService::Stub> stub_;
    public:
        ManagerDataBase_client();
        ManagerDataBase_client(std::shared_ptr<Channel> channel);
        void addManager(const people::Manager &manager) const override;
        void getManager(people::Manager &inputManager, const std::string &inputEmail) const override;
        [[nodiscard]] bool isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const override;
        std::string managerInfo(people::Manager &manager) const override;
        ~ManagerDataBase_client() override = default;
    };

    struct ClientDataBase_client : ClientRepository {
    private:
        std::unique_ptr<CRMService::Stub> stub_;
    public:
        ClientDataBase_client();
        ClientDataBase_client(std::shared_ptr<Channel> channel);
        void addClient(const people::Client &client, const std::string &managerEmail) const override;
        void deleteClient(const std::string &clientEmail, const std::string &managerEmail) const override;
        void updateAllClients(people::Manager &manager) const override;
        [[nodiscard]] std::string clientInfo(const people::Client &client) const override;
        [[nodiscard]] std::vector<std::string> getDealProcess(const people::Client &client) const override;
        ~ClientDataBase_client() override = default;
    };
} // namespace repositories

#endif //CRM_SYSTEM_STORAGEDATABASE_H
