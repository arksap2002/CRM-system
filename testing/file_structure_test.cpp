#include "doctest.h"
#include "people.h"
#include <sstream>

using namespace people;
using namespace testing;

TEST_CASE("Manager") {
    Manager m("Deins_mail@mail.ru", "Denis Shestakov Vladislavovich", "+7 (123) 456 78-90", "123321");
    add_manager(m);
    CHECK(get_current_password("Deins_mail@mail.ru", ss) == "123321");
    Manager new_m;
    get_manager(new_m, "Deins_mail@mail.ru", ss);
    CHECK(new_m.get_email() == "Deins_mail@mail.ru");
    CHECK(new_m.get_password() == "123321");
    CHECK(Testing::get_name_manager(new_m) == "Denis Shestakov Vladislavovich");
    CHECK(Testing::get_phone_manager(new_m) == "+7 (123) 456 78-90");
}

TEST_CASE("Clients") {
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    CHECK(ss.str() == "Read information about user\n");
    ss.str("");
    ss.clear();
    Client c1("1katana@gamail.com", "1-Turtle Leonardo", "232323", "Pizza");
    m.add_client(c1, ss);
    std::cout << ss.str() << "\n";
    CHECK(ss.str() == "Such client already exists\n");
    Client c2("2moneymoney@yandex.com", "2-Scrooge McDuck", "777777", "Oil");
    ss.str("");
    ss.clear();
    m.add_client(c2, ss);
    CHECK(ss.str() == "Such client already exists\n");
    m.load_clients();
    CHECK((m.list_clients.size() >= 2 || m.list_clients.size() <= 4));
    CHECK(Testing::get_name_client(m.list_clients[0]) == "1-Turtle Leonardo");
    CHECK(Testing::get_phone_client(m.list_clients[0]) == "232323");
    CHECK(Testing::get_email_client(m.list_clients[0]) == "1katana@gamail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[0]) == "Pizza");
    CHECK(Testing::get_name_client(m.list_clients[1]) == "2-Scrooge McDuck");
    CHECK(Testing::get_phone_client(m.list_clients[1]) == "777777");
    CHECK(Testing::get_email_client(m.list_clients[1]) == "2moneymoney@yandex.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[1]) == "Oil");
}

TEST_CASE("Add Client in list_clients") {
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    m.load_clients();
    Client c3("Earth&Water@yandex.com", "3-Potato", "0000", "Carrot");
    m.add_client(c3, ss);
    CHECK((m.list_clients.size() >= 2 || m.list_clients.size() <= 4));
    CHECK(Testing::get_name_client(m.list_clients[2]) == "3-Potato");
    CHECK(Testing::get_phone_client(m.list_clients[2]) == "0000");
    CHECK(Testing::get_email_client(m.list_clients[2]) == "Earth&Water@yandex.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[2]) == "Carrot");
}

TEST_CASE("Delete Client") {
    Manager m;
    std::stringstream ss;
    get_manager(m, "Deins_mail@mail.ru", ss);
    m.load_clients();
    Client c("BloodBlood@mail.ru", "4-Dracula", "666", "Blood");
    ss.str("");
    ss.clear();
    m.add_client(c, ss);
    CHECK(ss.str() == "Client successfully added\n");
    CHECK(m.list_clients.size() == 4);
    CHECK(Testing::get_name_client(m.list_clients[3]) == "4-Dracula");
    CHECK(Testing::get_phone_client(m.list_clients[3]) == "666");
    CHECK(Testing::get_email_client(m.list_clients[3]) == "BloodBlood@mail.ru");
    CHECK(Testing::get_deal_product_client(m.list_clients[3]) == "Blood");
    ss.str("");
    ss.clear();
    m.delete_client("BloodBlood@mail.ru", ss);
    CHECK(m.list_clients.size() == 3);
    CHECK(ss.str() == "Client successfully deleted\n");
}

TEST_CASE("Add second Manager") {
    Manager m("arksap@mail.ru", "Arkady Sapozhnikov", "-7 (321) 654 87-09", "010199");
    std::stringstream ss;
    add_manager(m, ss);
    Manager new_m;
    get_manager(new_m, "arksap@mail.ru", ss);
    CHECK(new_m.get_email() == "arksap@mail.ru");
    CHECK(new_m.get_password() == "010199");
    CHECK(Testing::get_name_manager(new_m) == "Arkady Sapozhnikov");
    CHECK(Testing::get_phone_manager(new_m) == "-7 (321) 654 87-09");
    Client c1("1katana@gamail.com", "1-Turtle Leonardo", "232323", "Pizza");
    m.add_client(c1, ss);
    Client c2("2ghoostcompany@gmail.com", "2-Scooby Doo", "93456789", "Cookies");
    ss.str("");
    ss.clear();
    m.add_client(c2, ss);
    m.load_clients();
    CHECK(m.list_clients.size() == 2);
    CHECK(Testing::get_name_client(m.list_clients[0]) == "1-Turtle Leonardo");
    CHECK(Testing::get_phone_client(m.list_clients[0]) == "232323");
    CHECK(Testing::get_email_client(m.list_clients[0]) == "1katana@gamail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[0]) == "Pizza");
    CHECK(Testing::get_name_client(m.list_clients[1]) == "2-Scooby Doo");
    CHECK(Testing::get_phone_client(m.list_clients[1]) == "93456789");
    CHECK(Testing::get_email_client(m.list_clients[1]) == "2ghoostcompany@gmail.com");
    CHECK(Testing::get_deal_product_client(m.list_clients[1]) == "Cookies");
}

TEST_CASE("Errors") {
    Manager m("arksap@mail.ru", "Arkady Sapozhnikov", "-7 (321) 654 87-09", "010199");
    std::stringstream ss;
    add_manager(m, ss);
    CHECK(ss.str() == "Such user already exists\n");
    Manager m1;
    ss.str("");
    ss.clear();
    get_manager(m1, "SomeThing@mail.ru", ss);
    CHECK(ss.str() == "Such user is not exists\n");
    ss.str("");
    ss.clear();
    get_manager(m1, "arksap@mail.ru", ss);
    Client c1("2ghoostcompany@gmail.com", "2-Scooby Doo", "93456789", "Cookies");
    ss.str("");
    ss.clear();
    m1.add_client(c1, ss);
    CHECK(ss.str() == "Such client already exists\n");
    ss.str("");
    ss.clear();
    m1.delete_client("abrakadabra@mail.ru", ss);
    CHECK(ss.str() == "Such client is not exists\n");
}

TEST_CASE("Update clients") {
    Manager m;
    std::stringstream ss;
    get_manager(m, "arksap@mail.ru", ss);
    m.load_clients();
    Testing::change_name1(m.list_clients[0]);
    m.update_clients();

    Manager mmm;
    get_manager(mmm, "arksap@mail.ru", ss);
    mmm.load_clients();
    CHECK(Testing::get_name_client(mmm.list_clients[0]) == "1-Naruto Uzumaki");
    Testing::change_name2(mmm.list_clients[0]);
    mmm.update_clients();
}