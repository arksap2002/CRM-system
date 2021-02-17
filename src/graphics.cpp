#include "graphics.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>


Application::Application(QWidget *parent)
        : QWidget(parent) {

    QPushButton *log_in_button = new QPushButton("Log in", this);
    QPushButton *register_button = new QPushButton("Register", this);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(log_in_button, 0, 0);
    grid->addWidget(register_button, 0, 1);

    setLayout(grid);

    connect(log_in_button, &QPushButton::clicked, this, &Application::LogIn);
    connect(register_button, &QPushButton::clicked, this, &Application::Register);

}


void Application::LogIn() {
    window()->close();
}

void Application::Register() {
    window()->close();
}


