#include "people.h"
#include <cmath>
#include <filesystem>

namespace people {
    people::Client::Client(std::string email_, std::string name_, std::string phone_, std::string deal_product_)
        : email(std::move(email_)), name(std::move(name_)), phone(std::move(phone_)),
          dealProduct(std::move(deal_product_)) {
        dealProcess = {{"Connection with client", false},
                       {"Concluding the contract", false},
                       {"Deal is completed", false}};
    }

    people::Client::Client() {
        dealProcess = {{"Connection with client", false},
                       {"Concluding the contract", false},
                       {"Deal is completed", false}};
    }

    people::Manager::Manager(std::string email_, std::string password_, std::string name_, std::string phone_)
        : email(std::move(email_)), password(std::move(password_)), name(std::move(name_)), phone(std::move(phone_)) {
    }
}// namespace people
