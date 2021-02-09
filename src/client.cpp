#include "client.h"

#include <utility>

namespace client {
    Client::Client(std::string name_, std::string surname_, std::string phone_, std::string email_)
        : name(std::move(name_)), surname(std::move(surname_)), phone(std::move(phone_)), email(std::move(email_)) {}
}// namespace client