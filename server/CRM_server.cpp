#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
    Status AddManager(ServerContext *context, const AddManagerRequest *request,
                      AddManagerReply *reply) override {
        // TODO use useCases, I have no idea how
        // TODO Here will be the realization of adding Manager to DataBase
//        sql << "select name, salary from persons where id = " << request->Manager->email,
//                into(request->Manager->name);
/*
        reply->set_managerId(request->manager->addManager());

        std::string path = static_cast<std::string>(fs::current_path()) + "/" + MANAGERS_RESORCES + "/" + manager.email;
        if (fs::exists(path)) { throw FileExists(); }
        std::ofstream out(path);
        out << manager.email << "\n"
            << manager.password << "\n"
            << manager.name << "\n"
            << manager.phone << "\n";
        out.close();
        fs::create_directory(static_cast<std::string>(fs::current_path()) + "/" + CLIENTS_RESORCES + "/" + manager.email);
*/
        return Status::OK;
    }
    Status GetManager(ServerContext *context, const GetManagerRequest *request,
                      GetManagerReply *reply) override {
//        reply->set_inputEmail(request->manager->addManager());
        return Status::OK;
    }
    Status IsCorrectPassword(ServerContext *context, const IsCorrectPasswordRequest *request,
                             IsCorrectPasswordReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status ManagerInfo(ServerContext *context, const ManagerInfoRequest *request,
                       ManagerInforReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status AddClient(ServerContext *context, const AddClientRequest *request,
                     AddClientReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status DeleteClient(ServerContext *context, const DeleteClientRequest *request,
                        DeleteClientReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status UpdateAllClients(ServerContext *context, const UpdateAllClientsRequest *request,
                            UpdateAllClientsReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status ClientInfo(ServerContext *context, const ClientInfoRequest *request,
                      ClientInfoReply *reply) override {
//        reply->set_managerId(request->manager->addManager());
        return Status::OK;
    }
    Status GetDealProcess(ServerContext *context, const GetDealProcessRequest *request,
                          GetDealProcessReply *reply) override {
//        reply->set_dealProcessInfo(request->manager->addManager());
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char **argv) {
    RunServer();

    return 0;
}
