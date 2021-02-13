#include <algorithm>
#include <fstream>
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

        friend std::ostream &operator<<(std::ostream &, const Client &);
        friend std::ifstream &operator>>(std::ifstream &, Client &);

        // Window Client card
    };

    std::ostream &operator<<(std::ostream &, const Client &);
    std::ifstream &operator>>(std::ifstream &, Client &);

    struct Manager {
    private:
        std::string name;
        std::string phone;
        std::string email;
        std::string password;
        std::string login;

    public:
        std::vector<Client> my_clients{};

        Manager(std::string, std::string, std::string, std::string, std::string);
        Manager() = default;
        [[nodiscard]] std::string get_password() const;
        [[nodiscard]] std::string get_login() const;

        friend std::ostream &operator<<(std::ostream &, const Manager &);
        friend std::ifstream &operator>>(std::ifstream &, Manager &);

        // Window Manager card
    };

    std::ostream &operator<<(std::ostream &, const Manager &);
    std::ifstream &operator>>(std::ifstream &, Manager &);
}// namespace people
#endif//CRM_SYSTEM_MANAGER_H
