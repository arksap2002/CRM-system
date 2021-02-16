#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#ifndef CRM_SYSTEM_MANAGER_H
#define CRM_SYSTEM_MANAGER_H
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
        void delete_client(const Client&, bool, std::ostream&);                     //delete "./resources/Clients/<email>/<Client.email>"
        void change_client(const Client&, std::ostream&);                           //change client from the "./resources/Clients/<email>/<Client.email>"

        friend void add_manager(const Manager&, std::ostream&);
        friend void get_manager(Manager&, const std::string&, std::ostream&);
    };
    std::string get_current_password(const std::string&, std::ostream &process);    //return password of std::string Manager + errors
    void add_manager(const Manager&, std::ostream&);                                //add Manager + errors
    void get_manager(Manager&, const std::string&, std::ostream&);                  //load information about this Manager
    void read_client(Client&, std::string&);
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
