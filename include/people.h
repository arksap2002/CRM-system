#ifndef CRM_SYSTEM_MANAGER_H
#define CRM_SYSTEM_MANAGER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "fwd.h"

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

        friend void read_client(std::vector<Client>& lst, const std::string& path);
        friend struct Manager;
        friend struct testing::Testing;
        friend struct Comp;
        // Window Client card
    };

    struct Manager {
    private:
        std::string name;
        std::string phone;
        std::string email;
        std::string password;

    public:
        std::vector<Client> list_clients{};

        Manager(std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_password() const;
        [[nodiscard]] std::string get_email() const;
        void load_clients();                                                        //load all clients from directory in the vector
        void add_client(const Client&, bool, std::ostream&);                        //add client to the "./resources/Clients/<email>/<Client.email>"
        void delete_client(const std::string&, bool, std::ostream&);                //delete "./resources/Clients/<email>/<Client.email>"
        void update_clients();                                                      //update all clients in the "./resources/Clients/<email>/<Client.email>"
                                                                                                                    //Be carefully! It can delete all files!

        friend void add_manager(const Manager&, std::ostream&);
        friend void get_manager(Manager&, const std::string&, std::ostream&);
        friend struct testing::Testing;
    };
    std::string get_current_password(const std::string&, std::ostream &process);    //return password of std::string Manager + errors
    void add_manager(const Manager&, std::ostream&);                                //add Manager + errors
    void get_manager(Manager&, const std::string&, std::ostream&);                  //load information about this Manager
    void read_client(Client&, std::string&);

    struct Comp{
        bool operator()(const Client&, const Client&);
    };
}// namespace people

namespace testing{
    struct Testing{
        static std::string get_name_manager(const people::Manager&);
        static std::string get_phone_manager(const people::Manager&);
        static std::string get_name_client(const people::Client&);
        static std::string get_phone_client(const people::Client&);
        static std::string get_email_client(const people::Client&);
        static std::string get_deal_product_client(const people::Client&);
        static void change_name1(people::Client&);
        static void change_name2(people::Client&);
    };
}// namespace testing
#endif//CRM_SYSTEM_MANAGER_H
