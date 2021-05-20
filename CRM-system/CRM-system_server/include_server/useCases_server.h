#ifndef GRPC_CRM_SYSTEM_USECASES_SERVER_H
#define GRPC_CRM_SYSTEM_USECASES_SERVER_H
#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"
#include "storageDataBase.h"

namespace useCasesServer{

    using namespace crm_system;

    struct UseCaseServerAddManager {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerAddManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int addManager(const AddManagerRequest *request) const;
    };

}

#endif //GRPC_CRM_SYSTEM_USECASES_SERVER_H
