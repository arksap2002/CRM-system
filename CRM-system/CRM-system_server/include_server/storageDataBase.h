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

    struct CrmSystemDataBase{
        sql::Driver *driver;
        sql::Connection *con;
        CrmSystemDataBase();
        int addManager(const AddManagerRequest *request);
        ~CrmSystemDataBase();
    };
}

#endif //GRPC_CRM_SYSTEM_STORAGEDATABASE_H
