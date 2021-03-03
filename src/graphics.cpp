#include "graphics.h"
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

people::Manager &MainWindow::GetManager() {
    return manager;
}

void MainWindow::SetManager(people::Manager &manager_) {
    manager = manager_;
}

GeneralWindow::GeneralWindow(QWidget *parent, people::Manager manager_) : QWidget(parent), manager(manager_) {

    if (manager.get_name() == "") {
        manager_name = new QLabel("error. need to update", this);
    } else {
        manager_name = new QLabel(QString::fromStdString(manager.get_name()), this);
    }

    QPushButton *managers_window_button = new QPushButton("Open managers window", this);
    QPushButton *clients_list_button = new QPushButton("Open clients list", this);

    grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(manager_name, 0, 0);
    grid->addWidget(managers_window_button, 1, 0);
    grid->addWidget(clients_list_button, 2, 0);

    setLayout(grid);

    connect(managers_window_button, &QPushButton::clicked, this, &GeneralWindow::OpenManagersAccount);
    connect(clients_list_button, &QPushButton::clicked, this, &GeneralWindow::OpenClientsWindow);

}

void GeneralWindow::redraw() {

    if (manager.get_name() != "") {
        manager_name->setText(QString::fromStdString(
                "Hello, " + manager.get_name() + "! Here is a general window. Here are some options:"));
        manager_name->update();
    }

}

void GeneralWindow::SetManager(people::Manager &manager_) {
    manager = manager_;
}


people::Manager &GeneralWindow::GetManager() {
    return manager;
}

void GeneralWindow::OpenManagersAccount() {
    managers_window.SetManager(GetManager());
    managers_window.redraw();
    managers_window.resize(1000, 700);
    managers_window.setWindowTitle("Your account");
    managers_window.show();
}

void GeneralWindow::OpenClientsWindow() {
    clients_window.SetManager(manager);
    clients_window.redraw();
    clients_window.resize(1000, 700);
    clients_window.setWindowTitle("Your clients list");
    clients_window.show();
}

ManagersWindow::ManagersWindow(QWidget *parent, people::Manager manager_) : QWidget(parent), manager(manager_) {

    if (manager.get_info() != "") {
        info = new QLabel(
                QString::fromStdString("Hello" + manager.get_name() + "!\n You personal info: " + manager.get_info()),
                this);
    } else {
        info = new QLabel("No manager. Error", this);
    }
    grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(info, 0, 0);

    setLayout(grid);
}

void ManagersWindow::SetManager(people::Manager &manager_) {
    manager = manager_;
}

void ManagersWindow::redraw() {
    if (manager.get_name() != "") {
        info->setText(
                QString::fromStdString("Hello " + manager.get_name() + "!\n You personal info: " + manager.get_info()));
    } else {
        info->setText("Error");
    }
    info->update();

}

AddClientsWindow::AddClientsWindow(QWidget *parent) : QWidget(parent) {

    QLabel *email = new QLabel("Input email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *name = new QLabel("Input name:", this);
    name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *phone = new QLabel("Input phone:", this);
    phone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QLabel *deal_product = new QLabel("Input deal_product:", this);
    deal_product->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    name_ = new QLineEdit(this);
    phone_ = new QLineEdit(this);
    deal_product_ = new QLineEdit(this);

    QPushButton *add_button = new QPushButton("Add", this);

    auto *grid = new QGridLayout(this);

    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(email, 1, 0);
    grid->addWidget(email_, 1, 1);
    grid->addWidget(name, 2, 0);
    grid->addWidget(name_, 2, 1);
    grid->addWidget(phone, 3, 0);
    grid->addWidget(phone_, 3, 1);
    grid->addWidget(deal_product, 4, 0);
    grid->addWidget(deal_product_, 4, 1);
    grid->addWidget(add_button, 5, 2);

    setLayout(grid);

    connect(add_button, &QPushButton::clicked, this, &AddClientsWindow::AddClient);

}

void AddClientsWindow::SetManager(people::Manager *manager_) {
    manager = *manager_;
}

void AddClientsWindow::AddClient() {
    manager.add_client({email_->text().toStdString(), name_->text().toStdString(), phone_->text().toStdString(),
                        deal_product_->text().toStdString()});
    email_->clear();
    name_->clear();
    phone_->clear();
    deal_product_->clear();
    this->close();
}

ClientsList::ClientsList(QWidget *parent) : QWidget(parent) {

    clients_data->setShowGrid(true);
    clients_data->setSelectionMode(QAbstractItemView::SingleSelection);
    clients_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    clients_data->setColumnCount(3);
    if (manager.get_name() != "") {
        this->CreateTable(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    }

    QPushButton *add_client_button = new QPushButton("Add client", this);
    QPushButton *update_button = new QPushButton("Update", this);

    grid = new QGridLayout(this);
    grid->addWidget(clients_data, 0, 0);
    grid->addWidget(add_client_button, 1, 1);
    grid->addWidget(update_button, 1, 2);
    grid = new QGridLayout(this);

    connect(add_client_button, &QPushButton::clicked, this, &ClientsList::OpenAddClientWindow);
    connect(update_button, &QPushButton::clicked, this, &ClientsList::redraw);

}

void ClientsList::OpenAddClientWindow() {
    add_clients_window.SetManager(&manager);
    add_clients_window.show();
}

void ClientsList::SetManager(people::Manager &manager_) {
    manager = manager_;
}

void ClientsList::redraw() {
    //CreateTable(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    int t = clients_data->rowCount();

    if ((int)manager.list_clients.size() > t) {
        for (; t < (int)manager.list_clients.size(); t++) {
            clients_data->insertRow(t);
            const people::Client &client = manager.list_clients[t];
            clients_data->setItem(t, 0, new QTableWidgetItem(QString::fromStdString(client.get_email())));
            clients_data->setItem(t, 1, new QTableWidgetItem(QString::fromStdString(client.get_name())));
            clients_data->setItem(t, 2, new QTableWidgetItem(QString::fromStdString(client.get_phone())));
        }
    }
    clients_data->update();
}

void ClientsList::CreateTable(const QStringList &headers) {

    int i = 0;
    clients_data->setHorizontalHeaderLabels(headers);
    for (const people::Client &client : manager.list_clients) {
        clients_data->insertRow(i);
        clients_data->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(client.get_email())));
        clients_data->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(client.get_name())));
        clients_data->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(client.get_phone())));
        i++;
    }
    clients_data->resizeColumnsToContents();
}


