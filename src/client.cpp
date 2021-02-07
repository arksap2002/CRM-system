#include "client.h"

namespace client {
    //I like to move it, move it
    Client::Client(std::string name_, std::string surname_) : name(std::move(name_)), surname(std::move(surname_)) {}

    std::string Client::getName() const {
        return name;
    }

    std::string Client::getSurname() const {
        return surname;
    }

    void Client::setName(std::string name_) {
        name = std::move(name_);
    }

    void Client::setSurname(std::string surname_) {
        surname = std::move(surname_);
    }
}// namespace client