#include "people.h"
#include "graphics.h"
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <QApplication>
#include <QWidget>


std::vector<people::Manager> managers;
std::set<std::pair<std::string, std::string>> passwords;
static const std::string CLIENTSFILE = "clients.txt";
static const std::string MANAGERFILE = "managers.txt";

/*void generalWindow(people::Manager &manager);

void cilentsWindow(people::Manager &manager);

void enterWindow();

void addClientWindow(people::Manager &manager) {
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
    cilentsWindow(manager);
}

void managerWindow(people::Manager &manager) {
    // open window
    std::cout << "Here is a manager window. Here are some options:" << '\n';
    std::cout << manager;
    std::cout << "1. Exit" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        generalWindow(manager);
    }
    assert(false);
}

void cilentsWindow(people::Manager &manager) {
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
        addClientWindow(manager);
    }
    if (number == 3) {
        generalWindow(manager);
    }
    assert(false);
}

void loginWindow() {
    // open window
    std::cout << "Here is a login window. To exit: 0 0. Input login and password" << '\n';
    std::string login, pass;
    std::cin >> login >> pass;
    //    TODO after Qt: no spaces in login and password
    if (login == "0" && pass == "0") {
        enterWindow();
    }
    if (passwords.find({login, pass}) != passwords.end()) {
        std::cout << "Welcome" << '\n';
        for (people::Manager &i : managers) {
            if (i.get_password() == pass && i.get_login() == login) {
                generalWindow(i);
            }
        }
        assert(false);
    } else {
        std::cout << "Try again" << '\n';
        loginWindow();
    }
}

*/
void RegisterWindow::RegisterManager() {
    std::string name, phone, email, login, pass;
    name = getName().toStdString();
    phone = getPhone().toStdString();
    email = getEmail().toStdString();
    login = getLogin().toStdString();
    pass = getPassword().toStdString();
    while (name.empty() || phone.empty() || email.empty() || login.empty() || pass.empty()) {
        errwind.resize(1500, 1000);
        errwind.setWindowTitle("Empty field");
        errwind.show();
    }
    if (passwords.find({login, pass}) != passwords.end()) {
        errwind.resize(1500, 1000);
        errwind.setWindowTitle("Manager already exists");
        errwind.show();
    }
    people::Manager manager(name, phone, email, login, pass);
    passwords.insert({login, pass});
    std::ofstream file(MANAGERFILE);
    assert(file.is_open());
    file << manager;
    file.close();
    std::cout << "Welcome" << '\n';
    //generalWindow(manager);
    //TODO открыть главное окно

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


/*void generalWindow(people::Manager &manager) {
    //возможно это вынести
    std::cout << "Here is a general window. Here are some options:" << '\n';
    std::cout << "1. Go to your manager account (button) " << '\n';
    std::cout << "2. Go to the clients window (button)" << '\n';
    std::cout << "3. Go to your deal list (button, not in the MVP) " << '\n';
    std::cout << "4. Exit (button)" << '\n';
    int number;
    std::cin >> number;
    if (number == 1) {
        managerWindow(manager);
    }
    if (number == 2) {
        cilentsWindow(manager);
    }
    if (number == 4) {
        enterWindow();
    }
    assert(false);
}
*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    preparation();
    MainWindow main_window;
    StartWindow start_window(&main_window);
    LoginWindow login_window(&main_window);
    RegisterWindow register_window(&main_window);
    GeneralWindow general_window(&main_window);
    ClientsList clients_list_window(&main_window);

    main_window.addTab(&start_window, "Start");
    main_window.addTab(&login_window, "Login");
    main_window.addTab(&register_window, "Registration");
    main_window.addTab(&general_window, "Main menu");
    main_window.addTab(&clients_list_window, "ClientsList");

    main_window.resize(2000, 1200);
    main_window.setWindowTitle("CRM-system");
    main_window.show();
    return app.exec();
}

