#ifndef CRM_SYSTEM_MANAGER_H
#define CRM_SYSTEM_MANAGER_H

#include "fwd.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace people {
    struct Client {
        std::string email;
        std::string name;
        std::string phone;
        std::string dealProduct;
        std::vector<std::pair<std::string, bool>> dealProcess;

        Client(std::string, std::string, std::string, std::string);

        Client();
    };

    struct Manager {
        std::string email;
        std::string password;
        std::string name;
        std::string phone;
    public:
        std::vector<Client> listClients{};

        Manager(std::string, std::string, std::string, std::string);

        Manager() = default;
    };
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
