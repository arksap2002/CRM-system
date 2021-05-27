#include "CRM-system_client.h"
#include <iostream>
#include <memory>
#include <string>

namespace repositories {

    ManagerException::ManagerException(const std::string& arg) : runtime_error(arg) {
    }

    ClientException::ClientException(const std::string& arg) : runtime_error(arg) {
    }

    using grpc::Channel;
    using grpc::ClientContext;
    using grpc::Status;

    using namespace crm_system;

    ManagerDataBase_client::ManagerDataBase_client()
            : stub_(CRMService::NewStub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()))) {
    }

    ManagerDataBase_client::ManagerDataBase_client(std::shared_ptr<Channel> channel) : stub_(CRMService::NewStub(channel)) {
    }

    ClientDataBase_client::ClientDataBase_client()
            : stub_(CRMService::NewStub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()))) {
    }

    ClientDataBase_client::ClientDataBase_client(std::shared_ptr<Channel> channel): stub_(CRMService::NewStub(channel)) {
    }

    namespace {
        void set_ClientGRPC(ClientGRPC *&clientGrpc, const people::Client &client) {
            clientGrpc->set_email(client.email);
            clientGrpc->set_name(client.name);
            clientGrpc->set_phone(client.phone);
            clientGrpc->set_dealproduct(client.dealProduct);
            for (auto &pointProcess : client.dealProcess) {
                DealProcessGRPC *dealProcessGrpc = clientGrpc->add_dealprocess();
                dealProcessGrpc->set_title(pointProcess.first);
                dealProcessGrpc->set_completed(pointProcess.second);
            }
        }

        void set_ManagerGRPC(ManagerGRPC *&managerGrpc, const people::Manager &manager) {
            managerGrpc->set_email(manager.email);
            managerGrpc->set_password(manager.password);
            managerGrpc->set_name(manager.name);
            managerGrpc->set_phone(manager.phone);
            for (const people::Client &client : manager.listClients) {
                ClientGRPC *clientGrpc = managerGrpc->add_listclients();
                set_ClientGRPC(clientGrpc, client);
            }
            managerGrpc->set_num_clients(manager.listClients.size());
        }

        void set_people_client(people::Client &client, const ClientGRPC& clientGrpc) {
            client.email = clientGrpc.email();
            client.name = clientGrpc.name();
            client.phone = clientGrpc.phone();
            client.dealProduct = clientGrpc.dealproduct();
            client.dealProcess.resize(3);
            for (int i = 0; i < 3; ++i){
//            client.dealProcess[i].first = clientGrpc->dealprocess(i).title();
                client.dealProcess[i].second = clientGrpc.dealprocess(i).completed();
            }
        }
    }
    void ManagerDataBase_client::addManager(const people::Manager &manager) const {
        AddManagerRequest request;
        ManagerGRPC* managerGrpc = new ManagerGRPC();
        set_ManagerGRPC(managerGrpc, manager);
        request.set_allocated_manager(managerGrpc);
        AddManagerReply reply;
        ClientContext context;
//        std::cout << "Server start addManager\n";
        Status status = stub_->AddManager(&context, request, &reply);
//        std::cout << "Server finish addManager\n";
        if (!status.ok()) {
            throw ManagerException("Server error. Can't add the manager");
        }
    }

    void ManagerDataBase_client::getManager(people::Manager &inputManager, const std::string &inputEmail) const {
        GetManagerRequest request;
//        request.set_inputManager(inputManager);
        request.set_inputemail(inputEmail);
        GetManagerReply reply;
        ClientContext context;
//        std::cout << "Server start getManager\n";
        Status status = stub_->GetManager(&context, request, &reply);
//        std::cout << "Server finish getManager\n";
        inputManager.email = reply.inputmanager().email();
        inputManager.password = reply.inputmanager().password();
        inputManager.name = reply.inputmanager().name();
        inputManager.phone = reply.inputmanager().phone();
        inputManager.listClients.resize(reply.inputmanager().num_clients());
        for (size_t i = 0; i < inputManager.listClients.size(); ++i){
            inputManager.listClients[i].dealProcess.resize(3);
            inputManager.listClients[i].dealProcess[0].first = "Connection with client";
            inputManager.listClients[i].dealProcess[1].first = "Concluding the contract";
            inputManager.listClients[i].dealProcess[2].first = "Deal is completed";
            set_people_client(inputManager.listClients[i], reply.inputmanager().listclients(i));
        }
        if (!status.ok()) {
            throw ManagerException("Server error. Can't get the manager");
        }
    }

    bool ManagerDataBase_client::isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const {
        IsCorrectPasswordRequest request;
        request.set_inputemail(inputEmail);
        request.set_inputpassword(inputPassword);
        IsCorrectPasswordReply reply;
        ClientContext context;
//        std::cout << "Server start isCorrectPassword\n";
        Status status = stub_->IsCorrectPassword(&context, request, &reply);
//        std::cout << "Server finish isCorrectPassword\n";
        if (!status.ok()) {
            throw ManagerException("Server error. Can't check the password");
        }
        return reply.find();
    }

    std::string ManagerDataBase_client::managerInfo(people::Manager &manager) const {
        return manager.email + " " + manager.name + " " + manager.phone;
    }

    void ClientDataBase_client::addClient(const people::Client &client, const std::string &managerEmail) const {
        for (int i = 0; i < 3; ++i){
            std::cout << client.dealProcess[i].first << " " << client.dealProcess[i].second << "\n";
        }
        AddClientRequest request;
        ClientGRPC* clientGrpc = new ClientGRPC();
        set_ClientGRPC(clientGrpc, client);
        request.set_allocated_client(clientGrpc);
        request.set_manageremail(managerEmail);
        AddClientReply reply;
        ClientContext context;
//        std::cout << "Server start add client\n";
        Status status = stub_->AddClient(&context, request, &reply);
//        std::cout << "Server finish add client\n";
        if (!status.ok()) {
            throw ClientException("Server error. Can't add the client");
        }
    }

    void ClientDataBase_client::deleteClient(const std::string &clientEmail, const std::string &managerEmail) const {
        DeleteClientRequest request;
        request.set_clientemail(clientEmail);
        request.set_manageremail(managerEmail);
        DeleteClientReply reply;
        ClientContext context;
//        std::cout << "Server start deleteClient\n";
        Status status = stub_->DeleteClient(&context, request, &reply);
//        std::cout << "Server finish deleteClient\n";
        if (!status.ok()) {
            throw ClientException("Server error. Can't delete the client");
        }
    }

    void ClientDataBase_client::updateAllClients(people::Manager &manager) const {
        UpdateAllClientsRequest request;
        request.set_manageremail(manager.email);
        UpdateAllClientsReply reply;
        ClientContext context;
//        std::cout << "Server start updateAllClients\n";
        Status status = stub_->UpdateAllClients(&context, request, &reply);
//        std::cout << "Server finish updateAllClients\n";
        if (!status.ok()) {
            throw ClientException("Server error. Can't update all clients");
        }
        manager.listClients.resize(reply.count_clients());
        for (int i = 0; i < reply.count_clients(); ++i){
            manager.listClients[i].dealProcess.resize(3);
            manager.listClients[i].dealProcess[0].first = "Connection with client";
            manager.listClients[i].dealProcess[1].first = "Concluding the contract";
            manager.listClients[i].dealProcess[2].first = "Deal is completed";
            set_people_client(manager.listClients[i], reply.listclients(i));
        }
    }

    std::string ClientDataBase_client::clientInfo(const people::Client &client) const {
        return client.email + " " + client.name + " " + client.phone;
    }

    std::vector<std::string> ClientDataBase_client::getDealProcess(const people::Client &client) const {
        std::vector<std::string> result(3);
        for (int i = 0; i < 3; ++i) {
            result[i] = client.dealProcess[i].first + ' ' + std::to_string(client.dealProcess[i].second);
        }
        return result;
    }
}// namespace repositories
