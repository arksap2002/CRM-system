#include "people.h"
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::vector<people::Manager> managers;
std::set<std::pair<std::string, std::string>> passwords;
std::set<std::string> managerEmails;
static const std::string CLIENTSFILE = "clients.txt";
static const std::string MANAGERFILE = "managers.txt";

void general_window(people::Manager &manager);
void cilents_window(people::Manager &manager);
void enter_window();

void addClient_window(people::Manager &manager) {
    // open window
    std::string name, phone, email;
    std::cout << "Input your name, skip: ~" << '\n';
    std::cin >> name;
    std::cout << "Input your phone, skip: ~" << '\n';
    std::cin >> phone;
    std::cout << "Input your email, skip: ~" << '\n';
    std::cin >> email;
    people::Client client(name, phone, email);
    manager.my_clients.push_back(client);
    std::ofstream file(CLIENTSFILE);
    assert(file);
    file << client;
    file << manager;
    file.close();
    std::cout << "Ready? - 1" << '\n';
    int number;
    std::cin >> number;
    assert(number == 1);
    cilents_window(manager);
}

void manager_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a manager window. Here are some options:" << '\n';
    std::cout << manager;
    std::cout << "1. Exit" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        general_window(manager);
    }
    assert(false);
}

void cilents_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a clients list:" << '\n';
    for (const people::Client &i : manager.my_clients) {
        std::cout << i;
    }
    std::cout << "Here is a clients window. Here are some options:" << '\n';
    std::cout << "1. Change someone (I can realize it only with buttons)" << '\n';
    std::cout << "2. Add someone (button)" << '\n';
    std::cout << "3. Exit (button)" << '\n';
    int number;
    std::cin >> number;
    if (number == 2) {
        addClient_window(manager);
    }
    if (number == 3) {
        general_window(manager);
    }
    assert(false);
}

void login_window() {
    // open window
    std::cout << "Here is a login window. To exit: 0 0. Input email and password" << '\n';
    std::string email, pass;
    std::cin >> email >> pass;
    //    TODO after Qt: no spaces in email and password
    if (email == "0" && pass == "0") {
        enter_window();
    }
    if (passwords.find({email, pass}) != passwords.end()) {
        std::cout << "Welcome" << '\n';
        for (people::Manager &i : managers) {
            if (i.get_password() == pass && i.get_login() == email) {
                general_window(i);
            }
        }
        assert(false);
    } else {
        std::cout << "Try again" << '\n';
        login_window();
    }
}

void registration_window() {
    // open window
    std::cout << "Here is a registration window. Input name, phone, email, password" << '\n';
    //    TODO have to fix input after Qt
    //    TODO add exit
    //    TODO fix std::cin >>
    std::string name, phone, email, pass;
    std::cin >> name >> phone >> email >> pass;
    people::Manager manager(name, phone, email, pass);
    if (managerEmails.find(manager.get_login()) != managerEmails.end()) {
        std::cout << "We have already have these" << '\n';
        registration_window();
    }
    managers.push_back(manager);
    passwords.insert({email, pass});
    std::ofstream file(MANAGERFILE);
    assert(file.is_open());
    file << manager;
    file.close();
    std::cout << "Welcome" << '\n';
    general_window(manager);
}

void preparation() {
    std::ifstream managersFile(MANAGERFILE);
    assert(managersFile.is_open());
    while (!managersFile.eof()) {
        people::Manager manager;
        managersFile >> manager;
        managers.push_back(manager);
        passwords.insert({manager.get_login(), manager.get_password()});
    }
    managersFile.close();
    std::ifstream dataFile(CLIENTSFILE);
    assert(dataFile.is_open());
    std::string line;
    while (!dataFile.eof()) {
        people::Client client;
        people::Manager manager;
        dataFile >> client;
        dataFile >> manager;
        manager.my_clients.push_back(client);
    }
    dataFile.close();
}

void enter_window() {
    // open window
    std::cout << "Log In - 0, register - 1" << '\n';
    int number;
    std::cin >> number;
    if (number == 0) {
        login_window();
    }
    if (number == 1) {
        registration_window();
    }
    assert(false);
}

void general_window(people::Manager &manager) {
    // open window
    std::cout << "Here is a general window. Here are some options:" << '\n';
    std::cout << "1. Go to your manager account (button) " << '\n';
    std::cout << "2. Go to the clients window (button)" << '\n';
    std::cout << "3. Go to your deal list (button, not in the MVP) " << '\n';
    std::cout << "4. Exit (button)" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        manager_window(manager);
    }
    if (number == 2) {
        cilents_window(manager);
    }
    if (number == 4) {
        enter_window();
    }
    assert(false);
}

int main() {
    preparation();
    enter_window();
}
