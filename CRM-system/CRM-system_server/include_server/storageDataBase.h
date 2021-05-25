#ifndef GRPC_CRM_SYSTEM_STORAGEDATABASE_H
#define GRPC_CRM_SYSTEM_STORAGEDATABASE_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <grpc++/grpc++.h>

#include "CRM-system.grpc.pb.h"

namespace storageSQL{

    using namespace crm_system;

    struct dataBaseError : std::runtime_error{
        dataBaseError(const std::string& file, const std::string& function, const sql::SQLException& e);
    };

    struct CrmSystemDataBase{
        sql::Driver *driver;
        sql::Connection *con;
        CrmSystemDataBase();
        int addManager(const AddManagerRequest *request,
                       AddManagerReply *reply);
        int getManager(const GetManagerRequest *request,
                       GetManagerReply *reply);
        int isCorrectPassword(const IsCorrectPasswordRequest *request,
                              IsCorrectPasswordReply *reply);
        int addClient(const AddClientRequest *request,
                      AddClientReply *reply);
        int deleteClient(const DeleteClientRequest *request,
                         DeleteClientReply *reply);
        int updateAllClients(const UpdateAllClientsRequest *request,
                             UpdateAllClientsReply *reply);
        ~CrmSystemDataBase();
    };
}

#endif //GRPC_CRM_SYSTEM_STORAGEDATABASE_H
