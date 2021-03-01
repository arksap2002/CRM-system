#ifndef CRM_SYSTEM_STORAGE_H
#define CRM_SYSTEM_STORAGE_H

#include "people.h"

namespace repositories {

    struct ManagerRepository {
        virtual void addManager(const people::Manager &manager) const = 0;
        virtual void getManager(people::Manager &input_manager, const std::string &input_email) const = 0;
        virtual void load_clients(people::Manager &manager) const = 0;
        [[nodiscard]] virtual bool is_correct_password(const std::string &input_email, const std::string &input_password) const = 0;
        virtual void managerInfo(people::Manager &manager) const = 0;
        virtual ~ManagerRepository() = default;
    };

}// namespace repositories
#endif//CRM_SYSTEM_STORAGE_H
