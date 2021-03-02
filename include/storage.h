#ifndef CRM_SYSTEM_STORAGE_H
#define CRM_SYSTEM_STORAGE_H

#include "people.h"

namespace repositories {

    struct ManagerRepository {
        virtual void addManager(const people::Manager &manager) const = 0;
        virtual void getManager(people::Manager &inputManager, const std::string &inputEmail) const = 0;
        [[nodiscard]] virtual bool isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const = 0;
        virtual std::string managerInfo(people::Manager &manager) const = 0;
        virtual ~ManagerRepository() = default;
    };

    struct ClientRepository {
        virtual void addClient(const people::Client &client, const std::string &managerEmail) const = 0;
        virtual void deleteClient(const std::string &clientEmail, const std::string &managerEmail) const = 0;
        virtual void updateAllClients(const people::Manager &manager) const = 0;
        virtual std::string clientInfo(const people::Client &client) const = 0;
        virtual std::vector<std::string> getDealProcess(const people::Client &client) const = 0;
        virtual ~ClientRepository() = default;
    };

}// namespace repositories
#endif//CRM_SYSTEM_STORAGE_H
