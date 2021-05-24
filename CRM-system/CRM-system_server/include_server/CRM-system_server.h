#ifndef GRPC_CRM_SYSTEM_CRM_SYSTEM_SERVER_H
#define GRPC_CRM_SYSTEM_CRM_SYSTEM_SERVER_H
#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"

#include "useCases_server.h"

namespace service {
    using grpc::Server;
    using grpc::ServerBuilder;
    using grpc::ServerContext;
    using grpc::Status;

    using namespace crm_system;

    class CRM_ServiceImpl final : public CRMService::Service {
        std::shared_ptr<storageSQL::CrmSystemDataBase> CrmSystemStorage;
        useCasesServer::UseCaseServerAddManager ucsAddManager;
    public:
        CRM_ServiceImpl();
    private:
        Status AddManager(ServerContext *context, const AddManagerRequest *request, AddManagerReply *reply) override;

        Status GetManager(ServerContext *context, const GetManagerRequest *request,
                          GetManagerReply *reply) override;

        Status IsCorrectPassword(ServerContext *context, const IsCorrectPasswordRequest *request,
                                 IsCorrectPasswordReply *reply) override;

        Status AddClient(ServerContext *context, const AddClientRequest *request,
                         AddClientReply *reply) override;

        Status DeleteClient(ServerContext *context, const DeleteClientRequest *request,
                            DeleteClientReply *reply) override;

        Status UpdateAllClients(ServerContext *context, const UpdateAllClientsRequest *request,
                                UpdateAllClientsReply *reply) override;
    };
}
#endif //GRPC_CRM_SYSTEM_CRM_SYSTEM_SERVER_H
