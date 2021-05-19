#include "storageDataBase.h"

namespace storageSQL{
    crmSystemDataBase::crmSystemDataBase() : driver(get_driver_instance()){
        //con = driver->connect("tcp://127.0.0.1:3306", "user_test", "password");

    }

    int crmSystemDataBase::addManager(const AddManagerRequest *request){

    }

    crmSystemDataBase::~crmSystemDataBase(){

    }
}