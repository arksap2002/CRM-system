#include <iostream>
#include <memory>
#include <string>
#include "people.h"
#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace crm_system;

class CRM_ServiceImpl final : public CRMService::Service {
    Status AddManager(ServerContext * context, const AddManagerRequest * request, AddManagerReply * reply) override{
        std::cout << "Add manager\n";
        reply->set_managerid(42);
        return Status::OK;
    }

    Status GetManager(ServerContext *context, const GetManagerRequest *request,
                      GetManagerReply *reply) override {
        std::cout << "Get manager\n";
        return Status::OK;
    }

    Status IsCorrectPassword(ServerContext *context, const IsCorrectPasswordRequest *request,
                             IsCorrectPasswordReply *reply) override {
        std::cout << "Check password\n";
        return Status::OK;
    }

    Status AddClient(ServerContext *context, const AddClientRequest *request,
                     AddClientReply *reply) override {
        std::cout << "Add client\n";
        return Status::OK;
    }

    Status DeleteClient(ServerContext *context, const DeleteClientRequest *request,
                        DeleteClientReply *reply) override {
        std::cout << "Delete client\n";
        return Status::OK;
    }

    Status UpdateAllClients(ServerContext *context, const UpdateAllClientsRequest *request,
                            UpdateAllClientsReply *reply) override {
        std::cout << "Update all clients\n";
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    CRM_ServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char ** argv) {
    RunServer();
    return 0;
}