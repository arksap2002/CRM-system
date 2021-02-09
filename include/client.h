#ifndef CRM_SYSTEM_CLIENT_H
#define CRM_SYSTEM_CLIENT_H

#include <string>

namespace client {
    struct Client {
    private:
        std::string name;
        std::string surname;
        std::string phone;
        std::string email;

    public:
        Client(std::string name_, std::string surname_, std::string phone_, std::string email_);
    };
}// namespace client

#endif//CRM_SYSTEM_CLIENT_H
