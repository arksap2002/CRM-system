#ifndef CRM_SYSTEM_STORAGE_H
#define CRM_SYSTEM_STORAGE_H

#include "people.h"

namespace repositories {

    struct ManagerRepository {
        virtual void addManager(const people::Manager &manager) const = 0;
        virtual ~ManagerRepository() = default;
    };

}// namespace repositories
#endif//CRM_SYSTEM_STORAGE_H
