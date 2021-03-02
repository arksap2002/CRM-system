#include "useCases.h"

namespace useCases {
    UseCaseAddManager::UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

    void UseCaseAddManager::addManager(const people::Manager &manager) const {
        try {
            managerRepository->addManager(manager);
        } catch (const repositories::FileExists &fileExists) {
//            std::cerr << repositories::FileExists::get_name() << "\n";
            throw fileExists;
        }
    }

    UseCaseGetManager::UseCaseGetManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

    void UseCaseGetManager::getManager(people::Manager &input_manager, const std::string &input_email) const {
        managerRepository->getManager(input_manager, input_email);
    }

    UseCaseIsCorrectPassword::UseCaseIsCorrectPassword(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

    bool UseCaseIsCorrectPassword::isCorrectPassword(const std::string &input_email, const std::string &input_password) const {
        try {
            return managerRepository->isCorrectPassword(input_email, input_password);
        } catch (const repositories::FileNotExists &fileNotExists) {
//            std::cerr << repositories::FileNotExists::get_name() << "\n";
            throw fileNotExists;
        }
    }
    UseCaseManagerInfo::UseCaseManagerInfo(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }
    std::string UseCaseManagerInfo::managerInfo(people::Manager &manager) const {
        return managerRepository->managerInfo(manager);
    }

    UseCaseAddClient::UseCaseAddClient(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    void UseCaseAddClient::addClient(const people::Client &client, const std::string &managerEmail) const {
        try {
            clientRepository->addClient(client, managerEmail);
        } catch (const repositories::FileExists &fileExists) {
//            std::cerr << repositories::FileExists::get_name() << "\n";
            throw fileExists;
        }
    }

    UseCaseDeleteClient::UseCaseDeleteClient(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    void UseCaseDeleteClient::deleteClient(const std::string &client_email, const std::string &managerEmail) const {
        try {
            return clientRepository->deleteClient(client_email, managerEmail);
        } catch (const repositories::FileNotExists &fileNotExists) {
//            std::cerr << repositories::FileNotExists::get_name() << "\n";
            throw fileNotExists;
        }
    }

    UseCaseUpdateAllClients::UseCaseUpdateAllClients(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    void UseCaseUpdateAllClients::updateAllClients(const people::Manager &manager) const {
        return clientRepository->updateAllClients(manager);
    }

    UseCaseClientInfo::UseCaseClientInfo(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    std::string UseCaseClientInfo::clientInfo(const people::Client &client) const {
        return clientRepository->clientInfo(client);
    }

    UseCaseGetDealProcess::UseCaseGetDealProcess(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }
    std::vector<std::string> UseCaseGetDealProcess::getDealProcess(const people::Client &client) const {
        return clientRepository->getDealProcess(client);
    }
}// namespace useCases