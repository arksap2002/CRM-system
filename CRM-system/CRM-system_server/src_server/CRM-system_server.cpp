#include "CRM-system_server.h"

namespace service{
using grpc::Server;
using grpc::ServerContext;
using grpc::Status;

using namespace crm_system;

CRM_ServiceImpl::CRM_ServiceImpl()
    : CrmSystemStorage(std::make_shared<storageSQL::CrmSystemDataBase>()), ucsAddManager(CrmSystemStorage),
    ucsGetManager(CrmSystemStorage), ucsIsCorrectPassword(CrmSystemStorage), ucsAddClient(CrmSystemStorage),
    ucsDeleteClient(CrmSystemStorage), ucsUpdateAllClients(CrmSystemStorage) {}

Status CRM_ServiceImpl::AddManager(ServerContext *context, const AddManagerRequest *request, AddManagerReply *reply) {
    std::cout << "Add manager" << std::endl;
    int id = ucsAddManager.addManager(request, reply);
//    reply->set_managerid(id);
    return Status::OK;
}

Status CRM_ServiceImpl::GetManager(ServerContext *context, const GetManagerRequest *request,
                  GetManagerReply *reply){
    std::cout << "Get manager\n";
    int id = ucsGetManager.getManager(request, reply);
    return Status::OK;
}

Status CRM_ServiceImpl::IsCorrectPassword(ServerContext *context, const IsCorrectPasswordRequest *request,
                         IsCorrectPasswordReply *reply){
    std::cout << "Check password\n";
    int id = ucsIsCorrectPassword.isCorrectPassword(request, reply);
    return Status::OK;
}

Status CRM_ServiceImpl::AddClient(ServerContext *context, const AddClientRequest *request,
                 AddClientReply *reply){
    std::cout << "Add client\n";
    int id = ucsAddClient.addClient(request, reply);
    return Status::OK;
}

Status CRM_ServiceImpl::DeleteClient(ServerContext *context, const DeleteClientRequest *request,
                    DeleteClientReply *reply){
    std::cout << "Delete client\n";
    int id = ucsDeleteClient.deleteClient(request, reply);
    return Status::OK;
}

Status CRM_ServiceImpl::UpdateAllClients(ServerContext *context, const UpdateAllClientsRequest *request,
                        UpdateAllClientsReply *reply) {
    std::cout << "Update all clients\n";
    int id = ucsUpdateAllClients.updateAllClients(request, reply);
    return Status::OK;
}
}