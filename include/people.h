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

const std::string RESOURCES = "resources";
const std::string MANAGERS_RESORCES = RESOURCES + "/Managers";
const std::string CLIENTS_RESORCES = RESOURCES + "/Clients";

namespace people {
    struct Client {
    private:
        std::string email;
        std::string name;
        std::string phone;
        std::string deal_product;
        std::vector<std::pair<std::string, bool>> deal_process;

    public:
        Client(std::string, std::string, std::string, std::string);
        Client();

        [[nodiscard]]std::vector<std::string> get_deal_process() const;
        [[nodiscard]]std::string get_info() const;

        friend void read_client(std::vector<Client> &lst, const std::string &path);
        friend struct Manager;
        friend struct testing::Testing;
        friend struct Comp;
        // Window Client card
    };

    struct Comp {
        bool operator()(const Client &, const Client &);
    };

    struct Manager {
    private:
        std::string email;
        std::string password;
        std::string name;
        std::string phone;

    public:
        std::vector<Client> list_clients{};

        Manager(std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_password() const;
        /* for testing */ [[nodiscard]] std::string get_email() const;
        void load_clients();                    //load all clients from directory in the vector
        void add_client(const Client &);        //add client to the "./resources/Clients/<email>/<Client.email>"
        void delete_client(const std::string &);//delete "./resources/Clients/<email>/<Client.email>"
        void update_clients();                  //update all clients in the "./resources/Clients/<email>/<Client.email>"
        [[nodiscard]]std::string get_info() const;

        friend void add_manager(const Manager &);
        friend void get_manager(Manager &, const std::string &);
        friend struct testing::Testing;
    };
    void add_manager(const Manager &);               //add Manager + errors
    void get_manager(Manager &, const std::string &);//load information about this Manager

    bool is_correct_password(const std::string &, const std::string &);
}// namespace people

namespace testing {
    struct Testing {
        static std::string get_name_manager(const people::Manager &);
        static std::string get_phone_manager(const people::Manager &);
        static std::string get_name_client(const people::Client &);
        static std::string get_phone_client(const people::Client &);
        static std::string get_email_client(const people::Client &);
        static std::string get_deal_product_client(const people::Client &);
        static void change_name1(people::Client &);
        static void change_name2(people::Client &);
    };
}// namespace testing
#endif//CRM_SYSTEM_MANAGER_H
