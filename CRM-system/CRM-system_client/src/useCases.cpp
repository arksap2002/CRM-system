#include "useCases.h"
#include "storage.h"

namespace repositories{
    StorageException::StorageException(const std::string& arg) : std::runtime_error(arg){}
};

namespace useCases {
    UseCaseAddManager::UseCaseAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_)
        : managerRepository(std::move(managerRepository_)) {
    }

    void UseCaseAddManager::addManager(const people::Manager &manager) const {
        try {
            managerRepository->addManager(manager);
        } catch (const repositories::StorageException &e) {
            std::cout << "Data exception: " << e.what() << "\n";
            throw e;
        } catch (const std::runtime_error &e){
            std::cout << "DataBase exception: " << e.what() << "\n";
            throw e;
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
        } catch (const repositories::StorageException &e) {
            std::cout << "Data exception: " << e.what() << "\n";
            throw e;
        } catch (const std::runtime_error &e){
            std::cout << "DataBase exception: " << e.what() << "\n";
            throw e;
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

    void UseCaseAddClient::addClient(const people::Client &client, people::Manager &manager) const {
        try {
            clientRepository->addClient(client, manager.email);
            manager.listClients.push_back(client);
        } catch (const repositories::StorageException &e) {
            std::cout << "Data exception: " << e.what() << "\n";
            throw e;
        } catch (const std::runtime_error &e){
            std::cout << "DataBase exception: " << e.what() << "\n";
            throw e;
        }
    }

    UseCaseDeleteClient::UseCaseDeleteClient(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    void UseCaseDeleteClient::deleteClient(const std::string &client_email, const std::string &managerEmail) const {
        try {
            clientRepository->deleteClient(client_email, managerEmail);
        } catch (const repositories::StorageException &e) {
            std::cout << "Data exception: " << e.what() << "\n";
            throw e;
        } catch (const std::runtime_error &e){
            std::cout << "DataBase exception: " << e.what() << "\n";
            throw e;
        }
    }

    UseCaseUpdateAllClients::UseCaseUpdateAllClients(std::unique_ptr<repositories::ClientRepository> clientRepository_)
        : clientRepository(std::move(clientRepository_)) {
    }

    void UseCaseUpdateAllClients::updateAllClients(people::Manager &manager) const {
        clientRepository->updateAllClients(manager);
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