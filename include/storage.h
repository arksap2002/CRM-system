#ifndef CRM_SYSTEM_STORAGE_H
#define CRM_SYSTEM_STORAGE_H

#include "people.h"

namespace repositories {

    class ManagerRepository {
    public:
        [[nodiscard]] virtual bool is_correct_password(const std::string &email, const std::string &inputPassword) const = 0;
        virtual void preparatoryCheck() const = 0;
        virtual void addManager(const people::Manager &manager) const = 0;
    };

}// namespace repositories
#endif//CRM_SYSTEM_STORAGE_H
