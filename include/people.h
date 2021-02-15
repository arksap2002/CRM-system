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
        std::string name;
        std::string phone;
        std::string email;

    public:
        Client(std::string, std::string, std::string);
        Client() = default;
        // Window Client card
    };

    struct Manager {
    private:
        std::string name;
        std::string phone;
        std::string email;
        std::string password;

    public:
        std::vector<Client> my_clients{};

        Manager(std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_password() const;
        [[nodiscard]] std::string get_email() const;
        friend void add_manager(const Manager&, std::ostream&);
        friend void get_manager(Manager&, const std::string&, std::ostream&);
    };
    std::string get_current_password(const std::string&, std::ostream &process);
    void add_manager(const Manager&, std::ostream&);
    void get_manager(Manager&, const std::string&, std::ostream&);
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
