#include "graphics.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>


ErrorWindow::ErrorWindow(QWidget *parent) : QWidget(parent) {
    errinfo = new QLabel("An error", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(errinfo);
    setLayout(grid);
}

RegisterWindow::RegisterWindow(QWidget *parent, MainWindow *mainwind_)
        : QWidget(parent), mainwind(mainwind_){

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
}

StartWindow::StartWindow(MainWindow *parent)
        : QWidget(parent) {

    QPushButton *log_in_button = new QPushButton("Log in", this);
    QPushButton *register_button = new QPushButton("Register", this);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(log_in_button, 0, 0);
    grid->addWidget(register_button, 0, 1);

    setLayout(grid);


    connect(log_in_button, &QPushButton::clicked, parent, &MainWindow::PushLogIn);
    connect(register_button, &QPushButton::clicked, parent, &MainWindow::PushRegister);

}


MainWindow::MainWindow(QWidget *parent) : QTabWidget(parent) {

}

void MainWindow::PushLogIn() {
    setCurrentIndex(1);
}

void MainWindow::PushRegister() {
    setCurrentIndex(2);
}

void MainWindow::ChangeToGeneral(MainWindow *parent) {
    parent->setCurrentIndex(4);
}

GeneralWindow::GeneralWindow(QWidget *parent) : QWidget(parent) {

}

AddClientsWindow::AddClientsWindow(QWidget *parent) : QWidget(parent) {

}

ManagersWindow::ManagersWindow(QWidget *parent) : QWidget(parent) {

}

ClientsList::ClientsList(QWidget *parent) : QWidget(parent) {

}


