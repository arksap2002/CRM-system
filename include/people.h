#ifndef CRM_SYSTEM_PEOPLE_H
#define CRM_SYSTEM_PEOPLE_H

#include "fwd.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

const std::string RESOURCES = "resources";
const std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
const std::string CLIENTS_RESORCES = RESOURCES + "/Clients";

namespace people {
    struct Client {
    protected:
        std::string email;
        std::string name;
        std::string phone;
        std::string deal_product;

    public:
        Client(std::string, std::string, std::string, std::string);
        Client();

        [[nodiscard]] virtual std::vector<std::string> get_deal_process() const;
        [[nodiscard]] virtual std::string get_info() const;

        friend struct Manager;
        friend struct testing::Testing;
        // Window Client card
    };

    struct Manager {
    protected:
        std::string email;
        std::string password;
        std::string name;
        std::string phone;

    public:
        std::vector<Client> list_clients{};

        Manager(std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_name() const;
        virtual void load_clients();                                                  //load all clients from directory in the vector
        virtual void add_client(const Client &);                                      //add client to the "./resources/Clients/<email>/<Client.email>"
        /* future */ [[maybe_unused]] virtual void delete_client(const std::string &);//delete "./resources/Clients/<email>/<Client.email>"
        /* future */ [[maybe_unused]] virtual void update_clients();                  //update all clients in the "./resources/Clients/<email>/<Client.email>"
        [[nodiscard]] virtual std::string get_info() const;

        friend struct Controller;
        friend struct testing::Testing;
    };


    struct Controller {
        virtual bool is_correct_password(const std::string &, const std::string &);
        virtual void add_manager(const Manager &);               //add Manager + errors
        virtual void get_manager(Manager &, const std::string &);//load information about this Manager
    };
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
