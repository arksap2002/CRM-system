#include "people.h"

namespace people {
    people::Client::Client(std::string name_, std::string phone_, std::string email_)
        : name(std::move(name_)), phone(std::move(phone_)), email(std::move(email_)) {
    }

    std::ostream &operator<<(std::ostream &os, const Client &client) {
        std::string name = client.name;
        std::replace(name.begin(), name.end(), ' ', '~');
        return os << name << ' ' << client.phone << ' ' << client.email << '\n';
    }

    std::ifstream &operator>>(std::ifstream &is, Client &client) {
        std::string name, email, phone;
        is >> name >> phone >> email;
        std::replace(name.begin(), name.end(), '~', ' ');
        client.email = email;
        client.phone = phone;
        client.name = name;
        return is;
    }

    people::Manager::Manager(std::string name_, std::string phone_, std::string email_,
                             std::string password_, std::string login_)
        : name(std::move(name_)), phone(std::move(phone_)), email(std::move(email_)),
          password(std::move(password_)), login(std::move(login_)) {
    }

    std::ostream &operator<<(std::ostream &os, const Manager &manager) {
        std::string name = manager.name;
        std::replace(name.begin(), name.end(), ' ', '~');
        return os << name << ' ' << manager.phone << ' ' << manager.email << '\n';
    }

    std::ifstream &operator>>(std::ifstream &is, Manager &manager) {
        std::string name, email, phone, login, password;
        is >> name >> phone >> email >> login >> password;
        std::replace(name.begin(), name.end(), '~', ' ');
        manager.name = name;
        manager.phone = phone;
        manager.email = email;
        manager.login = login;
        manager.password = password;
        return is;
    }

    std::string Manager::get_password() const {
        return password;
    }

    std::string Manager::get_login() const {
        return login;
    }
}// namespace people
