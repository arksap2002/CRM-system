#include "graphics.h"
#include "people.h"
#include "useCases.h"
#include <string>
#include "CRM-system_client.h"

using namespace people;
using namespace repositories;
using namespace useCases;

//void general_window(Manager &manager);
//void cilents_window(Manager &manager);
//void enter_window();

//void addClient_window(Manager &manager) {
//    // open window
//    std::string name, phone, email, deal_product;
//    //    TODO think about skip after Qt
//    //    TODO add exit button
//    std::cout << "Input your email, skip: ~\n";
//    std::cin >> email;
//    std::cout << "Input your name, skip: ~\n";
//    std::cin >> name;
//    std::cout << "Input your phone, skip: ~\n";
//    std::cin >> phone;
//    std::cout << "Input your deal product, skip: ~\n";
//    std::cin >> deal_product;
//    Client client(email, name, phone, deal_product);
//    UseCaseAddClient ucAddClient(std::make_unique<ClientFileSystem>());//!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    ucAddClient.addClient(client, manager);
//    std::cout << "Ready? - 1\n";
//    int number;
//    std::cin >> number;
//    assert(number == 1);
//    clients_window(manager);
//    assert(false);
//}
//
//void manager_window(Manager &manager) {
//    // open window
//    std::cout << "Hello, ";
//    std::cout << manager.name << '\n';
//    UseCaseManagerInfo ucManagerInfo(std::make_unique<ManagerFileSystem>());
//    std::cout << "Your personal info: " << ucManagerInfo.managerInfo(manager) << '\n';
//    std::cout << "Here is a manager window. Here are some options:\n";
//    std::cout << "1. Exit\n";
//    int number;
//    std::cin >> number;
//    if (number == 1) { general_window(manager); }
//    assert(false);
//}
//
//void deal_list_window(Manager &manager, int index) {
//    // open window
//    std::cout << "Here is a deal list window\n";
//    UseCaseGetDealProcess ucGetDealProcess(std::make_unique<ClientFileSystem>());//!!!!!!!!!!!!!!!!!!!!!!
//    UseCaseClientInfo ucClientInfo(std::make_unique<ClientFileSystem>());        //!!!!!!!!!!!!!!!!!!!!!!!
//    std::cout << "Here is your deal status for: " << ucClientInfo.clientInfo(manager.listClients[index]) << '\n';
//    std::vector<std::string> dealInfo = ucGetDealProcess.getDealProcess(manager.listClients[index]);
//    for (const auto &s : dealInfo) {
//        std::cout << s << '\n';
//    }
//    std::cout << "Here are some options:\n";
//    std::cout << "1. Exit (button)\n";
//    int number;
//    std::cin >> number;
//    assert(number == 1);
//    clients_window(manager);
//    assert(false);
//}
//
//void clients_window(Manager &manager) {
//    // open window
//    std::cout << "Here is a clients list:\n";
//    int index = 1;
//    for (const Client &client : manager.listClients) {
//        UseCaseClientInfo ucClientInfo(std::make_unique<ClientFileSystem>());//!!!!!!!!!!!!!!!!!
//        std::cout << index++ << ") " << ucClientInfo.clientInfo(client) << '\n';
//    }
//    std::cout << "Here is a clients window. Here are some options:\n";
//    std::cout << "1. Change someone (I can realize it only with buttons)\n";
//    std::cout << "2. Go to your deal list (button, not in the MVP) \n";
//    std::cout << "3. Add someone (button)\n";
//    std::cout << "4. Exit (button)\n";
//    int number;
//    std::cin >> number;
//    if (number == 2) {
//        std::cout << "Input the number of the client\n";
//        int n;
//        std::cin >> n;
//        deal_list_window(manager, n - 1);
//    }
//    if (number == 3) { addClient_window(manager); }
//    if (number == 4) { general_window(manager); }
//    assert(false);
//}

void LoginWindow::LoginManager() {
    std::string email, password;
    email = getEmail().toStdString();
    password = getPassword().toStdString();
    try {
        UseCaseIsCorrectPassword ucIsCorrectPassword(std::make_unique<ManagerDataBase_client>());
        if (!ucIsCorrectPassword.isCorrectPassword(email, password)) {
            error_window_login.resize(500, 500);
            error_window_login.setWindowTitle("Error");
            error_window_login.errinfo->setText("Incorrect password");
            error_window_login.errinfo->update();
            error_window_login.show();
            //std::cerr << "Incorrect password\n";
            //login_window();
        } else {
            Manager manager;
            mainwind->SetManager(manager);
            mainwind->ChangeToGeneral();
        }
    } catch (const std::exception &e) {
        error_window_login.resize(1000, 1000);
        error_window_login.setWindowTitle("Error");
        error_window_login.errinfo->setText("Such user is not exists. Try again");
        error_window_login.errinfo->update();
        error_window_login.show();
        //throw;
        //std::cerr << "Such user is not exists. Try again\n";
        //TODO окно ошибки
    }
}

void RegisterWindow::RegisterManager() {
    std::string name, phone, email, pass;
    try {
        email = getEmail().toStdString();
        name = getName().toStdString();
        phone = getPhone().toStdString();
        pass = getPassword().toStdString();
    } catch (...) {
        error_window_register.resize(1000, 1000);
        error_window_register.setWindowTitle("Error");
        error_window_register.errinfo->setText("You have not filled all the fields");
        error_window_register.errinfo->update();
        error_window_register.show();
        //throw;
    }
    Manager manager(email, pass, name, phone);
    try {
        UseCaseAddManager ucAddManager(std::make_unique<ManagerDataBase_client>());
        ucAddManager.addManager(manager);
    } catch (...) {
        error_window_register.resize(1000, 1000);
        error_window_register.setWindowTitle("Error");
        error_window_register.errinfo->setText("Account already exists");
        error_window_register.errinfo->update();
        error_window_register.show();
        mainwind->ChangeToStart();
        //throw;
    }
    mainwind->SetManager(manager);
    mainwind->ChangeToGeneral();
}


/*void general_window(Manager &manager) {
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
}*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window;
    StartWindow start_window(&main_window);
    LoginWindow login_window(&main_window);
    RegisterWindow register_window(&main_window);
    //GeneralWindow general_window(&main_window);
    //ClientsList clients_list_window(&main_window);

    main_window.addTab(&start_window, "Start");
    main_window.addTab(&login_window, "Login");
    main_window.addTab(&register_window, "Registration");
    //main_window.addTab(&general_window, "Main menu");
    //main_window.addTab(&clients_list_window, "ClientsList");

    main_window.resize(2000, 1200);
    main_window.setWindowTitle("CRM-system");
    main_window.show();
    return app.exec();
}
