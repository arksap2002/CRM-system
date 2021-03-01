#include "graphics.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include "people.h"

int start_window_num = 0;
int login_window_num = 1;
int registration_window_num = 2;
int general_window_num = 3;
int clients_window_num = 4;


ErrorWindow::ErrorWindow(QWidget *parent) : QWidget(parent) {
    errinfo = new QLabel("An error", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(errinfo);
    setLayout(grid);
}

RegisterWindow::RegisterWindow(MainWindow *parent)
        : QWidget(parent) {

    mainwind = parent;

    reginfo = new QLabel("Here is a registration window. Input email, name, phone, password", this);
    QLabel *email = new QLabel("Email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *name = new QLabel("Name:", this);
    name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *phone = new QLabel("Phone:", this);
    phone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *password = new QLabel("Password:", this);
    password->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    name_ = new QLineEdit(this);
    phone_ = new QLineEdit(this);
    password_ = new QLineEdit(this);

    QPushButton *register_button = new QPushButton("Register", this);

    auto *grid = new QGridLayout(this);

    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(reginfo, 0, 0);
    grid->addWidget(email, 1, 0);
    grid->addWidget(email_, 1, 1);
    grid->addWidget(name, 2, 0);
    grid->addWidget(name_, 2, 1);
    grid->addWidget(phone, 3, 0);
    grid->addWidget(phone_, 3, 1);
    grid->addWidget(password, 4, 0);
    grid->addWidget(password_, 4, 1);
    grid->addWidget(register_button, 5, 2);

    setLayout(grid);

    connect(register_button, &QPushButton::clicked, this, &RegisterWindow::RegisterManager);
}


QString RegisterWindow::getName() {
    return name_->text();
}

QString RegisterWindow::getPhone() {
    return phone_->text();
}

QString RegisterWindow::getEmail() {
    return email_->text();
}

QString RegisterWindow::getPassword() {
    return password_->text();
}


LoginWindow::LoginWindow(MainWindow *parent)
        : QWidget(parent) {

    mainwind = parent;

    logininfo = new QLabel("Here is a login window. Input email/login and password", this);
    QLabel *email = new QLabel("Email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *password = new QLabel("Password:", this);
    password->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    password_ = new QLineEdit(this);

    QPushButton *login_button = new QPushButton("Login", this);

    auto *grid = new QGridLayout(this);

    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(logininfo, 0, 0);
    grid->addWidget(email, 1, 0);
    grid->addWidget(email_, 1, 1);
    grid->addWidget(password, 2, 0);
    grid->addWidget(password_, 2, 1);
    grid->addWidget(login_button, 3, 2);

    setLayout(grid);

    connect(login_button, &QPushButton::clicked, this, &LoginWindow::LoginManager);

}

QString LoginWindow::getEmail() {
    return email_->text();
}

QString LoginWindow::getPassword() {
    return password_->text();
}

StartWindow::StartWindow(MainWindow *parent)
        : QWidget(parent) {

    QPushButton *log_in_button = new QPushButton("Log in", this);
    QPushButton *register_button = new QPushButton("Register", this);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(log_in_button, 0, 0);
    grid->addWidget(register_button, 0, 1);

    setLayout(grid);


    connect(log_in_button, &QPushButton::clicked, parent, &MainWindow::ChangeToLogIn);
    connect(register_button, &QPushButton::clicked, parent, &MainWindow::ChangeToRegister);

}


MainWindow::MainWindow(QWidget *parent) : QTabWidget(parent) {

}

void MainWindow::ChangeToStart() {
    setCurrentIndex(start_window_num);
}

void MainWindow::ChangeToLogIn() {
    setCurrentIndex(login_window_num);
}

void MainWindow::ChangeToRegister() {
    setCurrentIndex(registration_window_num);
}

void MainWindow::ChangeToGeneral() {
    general_window.SetManager(GetManager());
    general_window.redraw();
    addTab(&general_window, "General");
    setCurrentIndex(general_window_num);
}

void MainWindow::ChangeToClients() {
    setCurrentIndex(clients_window_num);
}

people::Manager& MainWindow::GetManager() {
    return *manager;
}

void MainWindow::SetManager(people::Manager &manager_) {
    manager = &manager_;
}

GeneralWindow::GeneralWindow(QWidget *parent, people::Manager *manager_) : QWidget(parent), manager(manager_) {

    if (manager == nullptr) {
        manager_name = new QLabel("error. need to update", this);
    } else {
        manager_name = new QLabel(QString::fromStdString(manager->get_name()), this);
    }

    grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(manager_name, 0, 0);
    setLayout(grid);
}

void GeneralWindow::redraw() {

    if (manager != nullptr) {
        manager_name->setText(QString::fromStdString("Hello, " + manager->get_name() + "! Here is a general window. Here are some options:"));
        manager_name->update();
    }

}

void GeneralWindow::SetManager(people::Manager &manager_) {
    manager = &manager_;
}

AddClientsWindow::AddClientsWindow(QWidget *parent) : QWidget(parent) {

}

ManagersWindow::ManagersWindow(QWidget *parent) : QWidget(parent) {

}

ClientsList::ClientsList(QWidget *parent) : QWidget(parent) {

}


