#include "testing.h"

namespace testing {
    std::string Testing::get_name_manager(const people::Manager &m) {
        return m.name;
    }

    std::string Testing::get_phone_manager(const people::Manager &m) {
        return m.phone;
    }

    std::string Testing::get_phone_client(const people::Client &c) {
        return c.phone;
    }

    std::string Testing::get_name_client(const people::Client &c) {
        return c.name;
    }

    std::string Testing::get_email_client(const people::Client &c) {
        return c.email;
    }

    std::string Testing::get_deal_product_client(const people::Client &c) {
        return c.deal_product;
    }

    void Testing::change_name1(people::Client &c) {
        c.name = "1-Naruto Uzumaki";
    }

    void Testing::change_name2(people::Client &c) {
        c.name = "1-Turtle Leonardo";
    }
}//namespace testing
