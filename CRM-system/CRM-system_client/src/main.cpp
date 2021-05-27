#include "CRM-system_client.h"
#include "graphics.h"
#include "people.h"
#include "useCases.h"
#include <string>

using namespace people;
using namespace repositories;
using namespace useCases;

// TODO fix registation
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
        } else {
            Manager manager;
            UseCaseGetManager ucGetManager(std::make_unique<ManagerDataBase_client>());
            ucGetManager.getManager(manager, email);
            mainwind->SetManager(manager);
            mainwind->ChangeToGeneral();
        }
    } catch (...) {
        error_window_login.resize(1000, 1000);
        error_window_login.setWindowTitle("Error");
        error_window_login.errinfo->setText("Such user does not exists. Try again");
        error_window_login.errinfo->update();
        error_window_login.show();
    }
}

void RegisterWindow::RegisterManager() {
    std::string name, phone, email, pass;
    try {
        email = getEmail().toStdString();
        name = getName().toStdString();
        phone = getPhone().toStdString();
        pass = getPassword().toStdString();
        if (email.empty() || name.empty() || phone == " " || pass.empty()) {
            throw std::logic_error("empty");
        }
    } catch (...) {
        error_window_register.resize(1000, 1000);
        error_window_register.setWindowTitle("Error");
        error_window_register.errinfo->setText("You have not filled all the fields");
        error_window_register.errinfo->update();
        error_window_register.show();
        mainwind->ChangeToStart();
        return;
    }

    Manager manager(email, pass, name, phone);
    try {
        UseCaseAddManager ucAddManager(std::make_unique<ManagerDataBase_client>());
        ucAddManager.addManager(manager);
        mainwind->SetManager(manager);
        mainwind->ChangeToGeneral();
    } catch (...) {
        error_window_register.resize(1000, 1000);
        error_window_register.setWindowTitle("Error");
        error_window_register.errinfo->setText("Account already exists");
        error_window_register.errinfo->update();
        error_window_register.show();
        mainwind->ChangeToStart();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow main_window;
    StartWindow start_window(&main_window);
    LoginWindow login_window(&main_window);
    RegisterWindow register_window(&main_window);
    GeneralWindow general_window(&main_window);
    ManagersWindow managers_window(&main_window);
    ClientsList clients_list_window(&main_window);
    AddClientsWindow add_clients_window(&main_window);


    main_window.stackedWidget->addWidget(&start_window);
    main_window.stackedWidget->addWidget(&login_window);
    main_window.stackedWidget->addWidget(&register_window);
    main_window.stackedWidget->addWidget(&general_window);
    main_window.stackedWidget->addWidget(&managers_window);
    main_window.stackedWidget->addWidget(&clients_list_window);
    main_window.stackedWidget->addWidget(&add_clients_window);

    main_window.resize(2000, 1200);
    main_window.setWindowTitle("CRM-system");
    main_window.show();
    return app.exec();
}
