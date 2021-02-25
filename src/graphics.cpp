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

RegisterWindow::RegisterWindow(QWidget *parent)
        : QWidget(parent) {

    reginfo = new QLabel("Here is a registration window. Input name, phone, email, login, password", this);
    QLabel *name = new QLabel("Name:", this);
    name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *phone = new QLabel("Phone:", this);
    phone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *email = new QLabel("Email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *login = new QLabel("Login:", this);
    login->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *password = new QLabel("Password:", this);
    password->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    le1 = new QLineEdit(this);
    le2 = new QLineEdit(this);
    le3 = new QLineEdit(this);
    le4 = new QLineEdit(this);
    le5 = new QLineEdit(this);

    QPushButton *register_button = new QPushButton("Register", this);

    auto *grid = new QGridLayout(this);

    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(reginfo, 0, 0);
    grid->addWidget(name, 1, 0);
    grid->addWidget(le1, 1, 1);
    grid->addWidget(phone, 2, 0);
    grid->addWidget(le2, 2, 1);
    grid->addWidget(email, 3, 0);
    grid->addWidget(le3, 3, 1);
    grid->addWidget(login, 4, 0);
    grid->addWidget(le4, 4, 1);
    grid->addWidget(password, 5, 0);
    grid->addWidget(le5, 5, 1);
    grid->addWidget(register_button, 6, 2);

    setLayout(grid);

    connect(register_button, &QPushButton::clicked, this, &RegisterWindow::RegisterManager);

}

QString RegisterWindow::getName() {
    return le1->text();
}

QString RegisterWindow::getPhone() {
    return le2->text();
}

QString RegisterWindow::getEmail() {
    return le3->text();
}

QString RegisterWindow::getLogin() {
    return le4->text();
}

QString RegisterWindow::getPassword() {
    return le5->text();
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

GeneralWindow::GeneralWindow(QWidget *parent) : QWidget(parent) {

}

AddClientsWindow::AddClientsWindow(QWidget *parent) : QWidget(parent) {

}

ManagersWindow::ManagersWindow(QWidget *parent) : QWidget(parent) {

}

ClientsList::ClientsList(QWidget *parent) : QWidget(parent) {

}




