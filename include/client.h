#ifndef CRM_SYSTEM_CLIENT_H
#define CRM_SYSTEM_CLIENT_H

#include <string>

namespace client {
    struct Client {
    private:
        std::string name;
        std::string surname;

    public:
        Client(std::string name_, std::string surname_);

        [[nodiscard]] std::string getName() const;

        [[nodiscard]] std::string getSurname() const;

        void setName(std::string name_);

        void setSurname(std::string surname_);
    };
}// namespace client

#endif//CRM_SYSTEM_CLIENT_H
