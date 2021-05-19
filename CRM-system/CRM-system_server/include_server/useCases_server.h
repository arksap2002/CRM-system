#ifndef GRPC_CRM_SYSTEM_USECASES_SERVER_H
#define GRPC_CRM_SYSTEM_USECASES_SERVER_H
#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"

namespace useCasesServer{

    struct UseCaseServerAddManager {
        std::unique_ptr<repositories::ManagerRepository> managerRepository;
        explicit UseCaseServerAddManager(std::unique_ptr<repositories::ManagerRepository> managerRepository_);
        void addManager(const people::Manager &manager) const;
    };

}

#endif //GRPC_CRM_SYSTEM_USECASES_SERVER_H
