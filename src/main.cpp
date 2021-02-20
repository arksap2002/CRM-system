#include "people.h"
#include <cassert>
#include <iostream>
#include <string>

void general_window(people::Manager &manager);
void cilents_window(people::Manager &manager);
void enter_window();

void addClient_window(people::Manager &manager) {
    // open window
    std::string name, phone, email, deal_product;
    //    TODO think about skip after Qt
    //    TODO add exit button
    std::cout << "Input your email, skip: ~\n";
    std::cin >> email;
    std::cout << "Input your name, skip: ~\n";
    std::cin >> name;
    std::cout << "Input your phone, skip: ~\n";
    std::cin >> phone;
    std::cout << "Input your deal product, skip: ~\n";
    std::cin >> deal_product;
    manager.add_client({email, name, phone, deal_product}, std::cout);
    std::cout << "Ready? - 1\n";
    int number;
    std::cin >> number;
    assert(number == 1);
    cilents_window(manager);
    assert(false);
}

void manager_window(people::Manager &manager) {
    // open window
    std::cout << "Hello, ";
    manager.print_info(std::cout);
    std::cout << "Here is a manager window. Here are some options:\n";
    std::cout << "1. Exit\n";
    int number;
    std::cin >> number;
    if (number == 1) { general_window(manager); }
    assert(false);
}

void deal_list_window(people::Manager &manager, int index) {
    // open window
    std::cout << "Here is a deal list window:\n";
    manager.list_clients[index].print_info(std::cout);
    manager.list_clients[index].print_deal_process(std::cout);
    std::cout << "Here are some options:\n";
    std::cout << "1. Exit (button)\n";
    int number;
    std::cin >> number;
    assert(number == 1);
    cilents_window(manager);
    assert(false);
}

void cilents_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a clients list:\n";
    int index = 1;
    for (people::Client client : manager.list_clients) {
        std::cout << index++ << ' ';
        client.print_info(std::cout);
    }
    std::cout << "Here is a clients window. Here are some options:\n";
    std::cout << "1. Change someone (I can realize it only with buttons)\n";
    std::cout << "2. Go to your deal list (button, not in the MVP) \n";
    std::cout << "3. Add someone (button)\n";
    std::cout << "4. Exit (button)\n";
    int number;
    std::cin >> number;
    if (number == 2) {
        std::cout << "Input the number of the client\n";
        int n;
        std::cin >> n;
        deal_list_window(manager, n);
    }
    if (number == 3) { addClient_window(manager); }
    if (number == 4) { general_window(manager); }
    assert(false);
}

void login_window() {
    // open window
    std::cout << "Here is a login window. To exit: 0 0. Input email and password\n";
    std::string email, password;
    std::cin >> email >> password;
    if (email == "0" && password == "0") { enter_window(); }
    //    TODO after Qt, check the no-spaces
    people::Manager manager;
    bool is_exists = people::get_manager(manager, email, std::cout);
    if (!is_exists) { login_window(); }
    bool is_password = manager.is_correct_password(password, std::cout);
    if (!is_password) { login_window(); }
    general_window(manager);
    assert(false);
}

void registration_window() {
    // open window
    std::cout << "Here is a registration window. Input email, name, phone, password\n";
    //    TODO add exit button in Qt
    std::string email, name, phone, password;
    std::cin >> email >> name >> phone >> password;
    people::Manager manager(email, name, phone, password);
    if (!people::add_manager(manager, std::cout)) { registration_window(); }
    std::cout << "Welcome\n";
    general_window(manager);
}

void enter_window() {
    // open window
    std::cout << "Log In - 0, register - 1\n";
    int number;
    std::cin >> number;
    if (number == 0) { login_window(); }
    if (number == 1) { registration_window(); }
    assert(false);
}

void general_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a general window. Here are some options:\n";
    std::cout << "1. Go to your manager account (button)\n";
    std::cout << "2. Go to the clients window (button)\n";
    std::cout << "3. Exit (button)\n";
    int number;
    std::cin >> number;
    if (number == 1) { manager_window(manager); }
    if (number == 2) { cilents_window(manager); }
    if (number == 3) { enter_window(); }
    assert(false);
}

int main() {
    enter_window();
}
