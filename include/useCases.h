#ifndef CRM_SYSTEM_USECASES_H
#define CRM_SYSTEM_USECASES_H
#include "storage.h"
#include "storageFileSystem.h"
#include <memory>

namespace useCases {

    struct UseCaseAddManager {
        std::shared_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseAddManager(std::shared_ptr<repositories::ManagerRepository> managerRepository_);
        void addManager(const people::Manager &manager) const;
    };

    struct UseCaseGetManager {
        std::shared_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseGetManager(std::shared_ptr<repositories::ManagerRepository> managerRepository_);
        void getManager(people::Manager &input_manager, const std::string &input_email) const;
    };

    struct UseCaseIsCorrectPassword {
        std::shared_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseIsCorrectPassword(std::shared_ptr<repositories::ManagerRepository> managerRepository_);
        [[nodiscard]] bool isCorrectPassword(const std::string &input_email, const std::string &input_password) const;
    };

    struct UseCaseManagerInfo {
        std::shared_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseManagerInfo(std::shared_ptr<repositories::ManagerRepository> managerRepository_);
        [[nodiscard]] std::string managerInfo(people::Manager &manager) const;
    };

    struct UseCaseAddClient {
        std::shared_ptr<repositories::ClientRepository> clientRepository;
        explicit UseCaseAddClient(std::shared_ptr<repositories::ClientRepository> clientRepository_);
        void addClient(const people::Client &client, const std::string &managerEmail) const;
    };

    struct UseCaseDeleteClient {
        std::shared_ptr<repositories::ClientRepository> clientRepository;
        explicit UseCaseDeleteClient(std::shared_ptr<repositories::ClientRepository> clientRepository_);
        void deleteClient(const std::string &client_email, const std::string &managerEmail) const;
    };

    struct UseCaseUpdateAllClients {
        std::shared_ptr<repositories::ClientRepository> clientRepository;
        explicit UseCaseUpdateAllClients(std::shared_ptr<repositories::ClientRepository> clientRepository_);
        void updateAllClients(const people::Manager &manager) const;
    };

    struct UseCaseClientInfo {
        std::shared_ptr<repositories::ClientRepository> clientRepository;
        explicit UseCaseClientInfo(std::shared_ptr<repositories::ClientRepository> clientRepository_);
        [[nodiscard]] std::string clientInfo(const people::Client &client) const;
    };

    struct UseCaseGetDealProcess {
        std::shared_ptr<repositories::ClientRepository> clientRepository;
        explicit UseCaseGetDealProcess(std::shared_ptr<repositories::ClientRepository> clientRepository_);
        [[nodiscard]] std::vector<std::string> getDealProcess(const people::Client &client) const;
    };
}// namespace useCases
#endif//CRM_SYSTEM_USECASES_H
