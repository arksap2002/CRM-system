#include "storageDataBase.h"
#include <iostream>
#include <memory>
#include <string>

namespace repositories {

    ManagerException::ManagerException(const std::string arg) : runtime_error(arg) {
    }

    ClientException::ClientException(const std::string arg) : runtime_error(arg) {
    }

    using CRMSystem::AddClientReply;
    using CRMSystem::AddClientRequest;
    using CRMsystem::AddManagerReply;
    using CRMsystem::AddManagerRequest;
    using CRMSystem::ClientInfoReply;
    using CRMSystem::ClientInfoRequest;
    using CRMsystem::CRMService;
    using CRMSystem::DeleteClientReply;
    using CRMSystem::DeleteClientRequest;
    using CRMSystem::GetDealProcessReply;
    using CRMSystem::GetDealProcessRequest;
    using CRMSystem::GetManagerReply;
    using CRMSystem::GetManagerRequest;
    using CRMSystem::IsCorrectPasswordReply;
    using CRMSystem::IsCorrectPasswordRequest;
    using CRMSystem::ManagerInfoReply;
    using CRMSystem::ManagerInfoRequest;
    using CRMSystem::UpdateAllClientsReply;
    using CRMSystem::UpdateAllClientsRequest;
    using grpc::Channel;
    using grpc::ClientContext;
    using grpc::Status;

    ManagerDataBase::ManagerDataBase(std::shared_ptr<Channel> channel) : stub_(Greeter::NewStub(channel)) {
    }


    void ManagerDataBase::addManager(const people::Manager &manager) const {
        AddManagerRequest request;
        request.set_manager(manager);
        AddManagerReply reply;
        ClientContext context;
        Status status = stub_->AddManager(&context, request, &reply);
        if (!status.ok()) {
            throw ManagerException("Server error. Can't add the manager");
        }
    }

    void ManagerDataBase::getManager(people::Manager &inputManager, const std::string &inputEmail) const {
        GetManagerRequest request;
        request.set_inputManager(inputManager);
        request.set_inputEmail(inputEmail);
        GetManagerReply reply;
        ClientContext context;
        Status status = stub_->GetManager(&context, request, &reply);
        if (!status.ok()) {
            throw ManagerException("Server error. Can't get the manager");
        }
    }

    bool ManagerDataBase::isCorrectPassword(const std::string &inputEmail, const std::string &inputPassword) const {
        IsCorrectPasswordRequest request;
        request.set_inputEmail(inputEmail);
        request.set_inputPassword(inputPassword);
        IsCorrectPasswordReply reply;
        ClientContext context;
        Status status = stub_->IsCorrectPassword(&context, request, &reply);
        if (!status.ok()) {
            throw ManagerException("Server error. Can't check the password");
        }
    }

    std::string ManagerDataBase::managerInfo(people::Manager &manager) const {
        ManagerInfoRequest request;
        request.set_manager(manager);
        ManagerInfoReply reply;
        ClientContext context;
        Status status = stub_->ManagerInfo(&context, request, &reply);
        if (!status.ok()) {
            throw ManagerException("Server error. Can't get the manager info");
        }
    }

    void addClient(const people::Client &client, const std::string &managerEmail) const {
        AddClientRequest request;
        request.set_client(client);
        request.set_managerEmail(managerEmail);
        AddClientReply reply;
        ClientContext context;
        Status status = stub_->AddClient(&context, request, &reply);
        if (!status.ok()) {
            throw ClientException("Server error. Can't add the client");
        }
    }
    void deleteClient(const std::string &clientEmail, const std::string &managerEmail) const {
        DeleteClientRequest request;
        request.set_clientEmail(clientEmail);
        request.set_managerEmail(managerEmail);
        DeleteClientReply reply;
        ClientContext context;
        Status status = stub_->DeleteClient(&context, request, &reply);
        if (!status.ok()) {
            throw ClientException("Server error. Can't delete the client");
        }
    }
    void updateAllClients(const people::Manager &manager) const {
        UpdateAllClientsRequest request;
        request.set_manager(manager);
        UpdateAllClientsReply reply;
        ClientContext context;
        Status status = stub_->UpdateAllClients(&context, request, &reply);
        if (!status.ok()) {
            throw ClientException("Server error. Can't update all clients");
        }
    }
    std::string clientInfo(const people::Client &client) const {
        ClientInfoRequest request;
        request.set_client(client);
        ClientInfoReply reply;
        ClientContext context;
        Status status = stub_->ClientInfo(&context, request, &reply);
        if (!status.ok()) {
            throw ClientException("Server error. Can't get the client info");
        }
    }
    std::vector<std::string> getDealProcess(const people::Client &client) const {
        GetDealProcessRequest request;
        request.set_client(client);
        GetDealProcessReply reply;
        ClientContext context;
        Status status = stub_->GetDealProcess(&context, request, &reply);
        if (!status.ok()) {
            throw ClientException("Server error. Can't get the deal process");
        }
    }
}// namespace repositories
