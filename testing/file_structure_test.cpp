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
    CHECK(Testing::get_name_manager(new_m) == "Denis Shestakov Vladislavovich");
    CHECK(Testing::get_phone_manager(new_m) == "+7 (123) 456 78-90");
};

TEST_CASE("Clients"){
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    CHECK(ss.str() == "Read information about user");
    ss.str("");
    ss.clear();
    Client c1("1-Turtle Leonardo", "232323", "katana@gamail.com", "Pizza");
    m.add_client(c1, false, ss);
    std::cout << ss.str() << "\n";
    CHECK(ss.str() == "Such client already exists");
    Client c2("2-Scrooge McDuck", "777777", "moneymoney@yandex.com", "Oil");
    ss.str("");
    ss.clear();
    m.add_client(c2, false, ss);
    CHECK(ss.str() == "Such client already exists");
    m.load_clients();
    CHECK((m.list_clients.size() >= 2 || m.list_clients.size() <= 4));
    CHECK(Testing::get_name_client(m.list_clients[0]) == "1-Turtle Leonardo");
    CHECK(Testing::get_phone_client(m.list_clients[0]) == "232323");
    CHECK(Testing::get_email_client(m.list_clients[0]) == "katana@gamail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[0]) == "Pizza");
    CHECK(Testing::get_name_client(m.list_clients[1]) == "2-Scrooge McDuck");
    CHECK(Testing::get_phone_client(m.list_clients[1]) == "777777");
    CHECK(Testing::get_email_client(m.list_clients[1]) == "moneymoney@yandex.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[1]) == "Oil");
}

TEST_CASE("Add Client in list_clients"){
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    m.load_clients();
    Client c3("3-Potato", "0000", "Earth&Water@yandex.com", "Carrot");
    m.add_client(c3, true, ss);
    CHECK((m.list_clients.size() >= 2 || m.list_clients.size() <= 4));
    CHECK(Testing::get_name_client(m.list_clients[2]) == "3-Potato");
    CHECK(Testing::get_phone_client(m.list_clients[2]) == "0000");
    CHECK(Testing::get_email_client(m.list_clients[2]) == "Earth&Water@yandex.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[2]) == "Carrot");
}

TEST_CASE("Delete Client"){
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    m.load_clients();
    Client c("4-Dracula", "666", "BloodBlood@mail.ru", "Blood");
    m.add_client(c, true, ss);
    CHECK(m.list_clients.size() == 4);
    CHECK(Testing::get_name_client(m.list_clients[3]) == "4-Dracula");
    CHECK(Testing::get_phone_client(m.list_clients[3]) == "666");
    CHECK(Testing::get_email_client(m.list_clients[3]) == "BloodBlood@mail.ru");
    CHECK(Testing::get_deal_product_client(m.list_clients[3]) == "Blood");
    m.delete_client("BloodBlood@mail.ru", true, ss);
    CHECK(m.list_clients.size() == 3);
}

TEST_CASE("Add second Manager"){
    Manager m("Arkady Sapognikov", "-7 (321) 654 87-09", "arksap@mail.ru", "010199");
    std::stringstream ss;
    add_manager(m, ss);
    Manager new_m;
    get_manager(new_m, "arksap@mail.ru", ss);
    CHECK(new_m.get_email() == "arksap@mail.ru");
    CHECK(new_m.get_password() == "010199");
    CHECK(Testing::get_name_manager(new_m) == "Arkady Sapognikov");
    CHECK(Testing::get_phone_manager(new_m) == "-7 (321) 654 87-09");
    Client c1("1-Turtle Leonardo", "232323", "katana@gamail.com", "Pizza");
    m.add_client(c1, false, ss);
    Client c2("2-Scooby Doo", "93456789", "ghoostcompany@gmail.com", "Cookies");
    ss.str("");
    ss.clear();
    m.add_client(c2, false, ss);
    m.load_clients();
    CHECK(m.list_clients.size() == 2);
    CHECK(Testing::get_name_client(m.list_clients[0]) == "1-Turtle Leonardo");
    CHECK(Testing::get_phone_client(m.list_clients[0]) == "232323");
    CHECK(Testing::get_email_client(m.list_clients[0]) == "katana@gamail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[0]) == "Pizza");
    CHECK(Testing::get_name_client(m.list_clients[1]) == "2-Scooby Doo");
    CHECK(Testing::get_phone_client(m.list_clients[1]) == "93456789");
    CHECK(Testing::get_email_client(m.list_clients[1]) == "ghoostcompany@gmail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[1]) == "Cookies");
}

TEST_CASE("Errors"){

}