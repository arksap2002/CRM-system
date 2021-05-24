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
        int addManager(const AddManagerRequest *request, AddManagerReply *reply) const;
    };

    struct UseCaseServerGetManager {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerGetManager(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int getManager(const GetManagerRequest *request, GetManagerReply *reply) const;
    };

    struct UseCaseServerIsCorrectPassword {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerIsCorrectPassword(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int isCorrectPassword(const IsCorrectPasswordRequest *request, IsCorrectPasswordReply *reply) const;
    };

    struct UseCaseServerAddClient {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerAddClient(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int addClient(const AddClientRequest *request, AddClientReply *reply) const;
    };

    struct UseCaseServerDeleteClient {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerDeleteClient(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int deleteClient(const DeleteClientRequest *request, DeleteClientReply *reply) const;
    };

    struct UseCaseServerUpdateAllClients {
        std::shared_ptr<storageSQL::CrmSystemDataBase> database;
        explicit UseCaseServerUpdateAllClients(std::shared_ptr<storageSQL::CrmSystemDataBase> database_);
        int updateAllClients(const UpdateAllClientsRequest *request, UpdateAllClientsReply *reply) const;
    };
}

#endif //GRPC_CRM_SYSTEM_USECASES_SERVER_H
