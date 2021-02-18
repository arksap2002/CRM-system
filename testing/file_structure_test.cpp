#include "doctest.h"
#include "people.h"
#include <sstream>

using namespace people;

TEST_CASE("Manager"){
    Manager m("Denis Shestakov Vladislavovich", "+7 (123) 456 78-90", "Deins_mail@mail.ru", "123321");
    std::stringstream ss;
    add_manager(m, ss);
    CHECK(ss.str() == "Such user already exists");
    ss.str("");
    ss.clear();
    CHECK(get_current_password("Deins_mail@mail.ru", ss) == "123321");
    ss.str("");
    ss.clear();
    Manager new_m;
    get_manager(new_m, "Deins_mail@mail.ru", ss);
    CHECK(new_m.get_email() == "Deins_mail@mail.ru");
    CHECK(new_m.get_password() == "123321");
    Testing test;
    CHECK(test.get_name(new_m) == "Denis Shestakov Vladislavovich");
    CHECK(test.get_phone(new_m) == "+7 (123) 456 78-90");
};

TEST_CASE("Clients"){
    
}