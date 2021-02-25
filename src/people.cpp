#include "people.h"

namespace people {
    people::Client::Client(std::string email_, std::string name_, std::string phone_, std::string deal_product_)
            : email(std::move(email_)), name(std::move(name_)), phone(std::move(phone_)), deal_product(std::move(deal_product_)) {
    }

    people::Client::Client() = default;

}// namespace people
