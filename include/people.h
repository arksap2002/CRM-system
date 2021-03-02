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

//const std::string RESOURCES = "resources";
//const std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
//const std::string CLIENTS_RESORCES = RESOURCES + "/Clients";

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

    /*[[nodiscard]] std::string get_info() const;
    [[nodiscard]] std::vector<std::string> get_deal_process() const;
    friend void read_client(std::vector<Client> &lst, const std::string &path);
    friend struct Manager;
    friend struct testing::Testing;
    friend struct Comp;
    // Window Client card

struct Comp {
    bool operator()(const Client &, const Client &);
};*/

    struct Manager {
        std::string email;
        std::string password;
        std::string name;
        std::string phone;
        std::vector<Client> listClients{};

        Manager(std::string, std::string, std::string, std::string);

        Manager() = default;
    };

    /*void load_clients();                                                  //load all clients from directory in the vector
    void add_client(const Client &);                                      //add client to the "./resources/Clients/<email>/<Client.email>"
    *//* future *//* [[maybe_unused]] void delete_client(const std::string &);//delete "./resources/Clients/<email>/<Client.email>"
    *//* future *//* [[maybe_unused]] void update_clients();                  //update all clients in the "./resources/Clients/<email>/<Client.email>"
        [[nodiscard]] std::string get_info() const;

        friend void add_manager(const Manager &);
        friend void get_manager(Manager &, const std::string &);
        friend struct testing::Testing;
    };
    void add_manager(const Manager &);               //add Manager + errors
    void get_manager(Manager &, const std::string &);//load information about this Manager

    bool is_correct_password(const std::string &, const std::string &);*/
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
