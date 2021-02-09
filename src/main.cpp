#include "client.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<client::Client> clients;
std::set<std::pair<std::string, std::string>> passwords;

void generalWindow();
void cilentsWindow();
void enterWindow();

void addClientWindow() {
    // open window
    std::cout << "Input your name, skip: -" << '\n';
    std::string name;
    std::cin >> name;
    std::cout << "Input your surname, skip: -" << '\n';
    std::string surname;
    std::cin >> surname;
    std::cout << "Input your phone, skip: -" << '\n';
    std::string phone;
    std::cin >> phone;
    std::cout << "Input your email, skip: -" << '\n';
    std::string email;
    std::cin >> email;
    std::ofstream file;
    file.open("clientsFile.txt");
    if (file.is_open()) {
        file << name << ' ' << surname << ' ' << phone << ' ' << email << '\n';
        file.close();
    }
    std::cout << "Ready? - 1" << '\n';
    int number;
    std::cin >> number;
    cilentsWindow();
}

void managerWindow() {
    // open window
    //    TODO: I'll do it in Sunday
    std::cout << "Here is a manager window. Here are some options:" << '\n';
    std::cout << "1. Exit" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        generalWindow();
    }
}

void cilentsWindow() {
    // open window
    std::cout << "Here is a clients list: Look (turn on your imagination):" << '\n';
    std::cout << "Here is a clients window. Here are some options:" << '\n';
    std::cout << "1. Change someone (I can realize it only with buttons)" << '\n';
    std::cout << "2. Add someone (button)" << '\n';
    std::cout << "3. Exit (button)" << '\n';
    int number;
    std::cin >> number;
    if (number == 2) {
        addClientWindow();
    }
    if (number == 3) {
        generalWindow();
    }
}

void loginWindow() {
    // open window
    std::cout << "Here is a login window. To exit: 0 0. Input login and password" << '\n';
    std::string login, password;
    std::cin >> login >> password;
    if (login == "0" && password == "0") {
        enterWindow();
    }
    if (passwords.find({login, password}) != passwords.end()) {
        std::cout << "Welcome" << '\n';
        generalWindow();
    } else {
        std::cout << "Try again" << '\n';
        loginWindow();
    }
}

void registrationWindow() {
    // open window
    std::cout << "Here is a registration window. To exit: 0 0. Input login and password" << '\n';
    std::string login, password;
    std::cin >> login >> password;
    if (login == "0" && password == "0") {
        enterWindow();
    }
    passwords.insert({password, login});
    std::ofstream file;
    file.open("passwords.txt");
    if (file.is_open()) {
        file << login << ' ' << password << '\n';
        file.close();
    }
    std::cout << "Welcome" << '\n';
    generalWindow();
}

void preparation() {
    //    It is not a window!!!
    //    Filling lists here.
    //    It is really bad realization, we will use it only in the MVP.
    std::ifstream passwordsFile;
    passwordsFile.open("passwords.txt");
    if (passwordsFile.is_open()) {
        std::string line;
        while (getline(passwordsFile, line)) {
            std::string login, password;
            std::istringstream iss(line);
            iss >> login >> password;
            passwords.insert({login, password});
        }
        passwordsFile.close();
    }
    std::ifstream clientsFile;
    clientsFile.open("clientsList.txt");
    if (clientsFile.is_open()) {
        std::string line;
        while (getline(clientsFile, line)) {
            std::string name, surname, phone, email;
            std::istringstream iss(line);
            iss >> surname >> name >> phone >> email;
            clients.emplace_back(surname, name, phone, email);
        }
        clientsFile.close();
    }
}

void enterWindow() {
    // open window
    std::cout << "Log In - 0, register - 1" << '\n';
    int number;
    std::cin >> number;
    if (number == 0) {
        loginWindow();
    } else {
        registrationWindow();
    }
}

void generalWindow() {
    // open window
    std::cout << "Here is a general window. Here are some options:" << '\n';
    std::cout << "1. Go to your manager account (button) " << '\n';
    std::cout << "2. Go to the clients window (button)" << '\n';
    std::cout << "3. Go to your deal list (button, not in the MVP) " << '\n';
    std::cout << "4. Exit (button)" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        managerWindow();
    }
    if (number == 2) {
        cilentsWindow();
    }
    if (number == 4) {
        enterWindow();
    }
}

int main() {
    preparation();
    enterWindow();
}
