#include "graphics.h"
#include "storage.h"
#include "storageFileSystem.h"
#include "useCases.h"

//TODO make just one manager later, remove all sets (Done?)
//TODO think about "QLayout: Attempting to add QLayout "" to QWidget "", which already has a layout" problem
//TODO think about global var manager, we have to implement it here, because multiply definition in graphics.h
//TODO remove graphics.h from add_executable in CMake
//TODO remove tabs

using namespace people;
using namespace repositories;
using namespace useCases;


//TODO maybe enum?
int start_window_num = 0;
int login_window_num = 1;
int registration_window_num = 2;
int general_window_num = 3;
int clients_window_num = 4;


people::Manager manager = people::Manager();

//TODO it later
ErrorWindow::ErrorWindow(QWidget *parent) : QWidget(parent) {

    errinfo = new QLabel("Error", this);

    auto *grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);
    grid->addWidget(errinfo);
    setLayout(grid);
}

RegisterWindow::RegisterWindow(MainWindow *parent)
    : QWidget(parent) {

    mainwind = parent;
    mainwind->stackedWidget->addWidget(this);

    reginfo = new QLabel("Here is a registration window. Input email, name, phone, password", this);
    auto *email = new QLabel("Email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *name = new QLabel("Name:", this);
    name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *phone = new QLabel("Phone:", this);
    phone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *password = new QLabel("Password:", this);
    password->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    name_ = new QLineEdit(this);
    phone_ = new QLineEdit(this);
    password_ = new QLineEdit(this);

    auto *register_button = new QPushButton("Register", this);

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


QString RegisterWindow::getName() const {
    return name_->text();
}

QString RegisterWindow::getPhone() const {
    return phone_->text();
}

QString RegisterWindow::getEmail() const {
    return email_->text();
}

QString RegisterWindow::getPassword() const {
    return password_->text();
}


LoginWindow::LoginWindow(MainWindow *parent)
    : QWidget(parent) {

    mainwind = parent;
    mainwind->stackedWidget->addWidget(this);

    logininfo = new QLabel("Here is a login window. Input email/login and password", this);
    auto *email = new QLabel("Email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *password = new QLabel("Password:", this);
    password->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    password_ = new QLineEdit(this);

    auto *login_button = new QPushButton("Login", this);

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

QString LoginWindow::getEmail() const {
    return email_->text();
}

QString LoginWindow::getPassword() const {
    return password_->text();
}

StartWindow::StartWindow(MainWindow *parent)
    : QWidget(parent) {

    parent->stackedWidget->addWidget(this);

    auto *log_in_button = new QPushButton("Log in", this);
    auto *register_button = new QPushButton("Register", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(log_in_button, 0, 0);
    grid->addWidget(register_button, 0, 1);

    setLayout(grid);


    connect(log_in_button, &QPushButton::clicked, parent, &MainWindow::ChangeToLogIn);
    connect(register_button, &QPushButton::clicked, parent, &MainWindow::ChangeToRegister);
}


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
}

void MainWindow::ChangeToStart() {
    stackedWidget->setCurrentIndex(start_window_num);
}

void MainWindow::ChangeToLogIn() {
    stackedWidget->setCurrentIndex(login_window_num);
}

void MainWindow::ChangeToRegister() {
    stackedWidget->setCurrentIndex(registration_window_num);
}

void MainWindow::ChangeToGeneral() {
    general_window.redraw();
    stackedWidget->addWidget(&general_window);
    stackedWidget->setCurrentIndex(general_window_num);
}

void MainWindow::ChangeToClients() {
    stackedWidget->setCurrentIndex(clients_window_num);
}
// TODO clang-tidy, can be static?
void MainWindow::SetManager(const people::Manager &manager_) {
    manager = manager_;
}
// TODO why unused?
GeneralWindow::GeneralWindow(QWidget *parent) : QWidget(parent) {
    if (manager.name.empty()) {
        manager_name = new QLabel("error. need to update", this);
    } else {
        manager_name = new QLabel(QString::fromStdString(manager.name), this);
    }

    auto *managers_window_button = new QPushButton("Open managers window", this);
    auto *clients_list_button = new QPushButton("Open clients list", this);

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
// TODO clang-tidy, can be const?
void GeneralWindow::redraw() {
    if (!manager.name.empty()) {
        manager_name->setText(QString::fromStdString(
                "Hello, " + manager.name + "! Here is a general window. Here are some options:"));
        manager_name->update();
    }
}

void GeneralWindow::OpenManagersAccount() {
    managers_window.redraw();
    managers_window.resize(1000, 700);
    managers_window.setWindowTitle("Your account");
    managers_window.show();
}

void GeneralWindow::OpenClientsWindow() {
    clients_window.redraw();
    clients_window.resize(1000, 700);
    clients_window.setWindowTitle("Your clients list");
    clients_window.show();
}
// TODO why unused?
ManagersWindow::ManagersWindow(QWidget *parent) : QWidget(parent) {
    UseCaseManagerInfo ucManagerInfo(std::make_unique<ManagerFileSystem>());
    // TODO WTF why you did'n check only the name like in manager redraw; and why it can be empty?))
    if (!ucManagerInfo.managerInfo(manager).empty()) {
        info = new QLabel(
                QString::fromStdString("Hello" + manager.name + "!\n You personal info: " + ucManagerInfo.managerInfo(manager)),
                this);
    } else {
        info = new QLabel("No manager. Error", this); // TODO think about this)))
    }
    grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);
    grid->addWidget(info, 0, 0);
    setLayout(grid);
}
// TODO clang-tidy, can be const?
void ManagersWindow::redraw() {
    UseCaseManagerInfo ucManagerInfo(std::make_unique<ManagerFileSystem>());
    //TODO WTF: Manager name may be empty?
    if (!manager.name.empty()) {
        info->setText(
                QString::fromStdString("Hello " + manager.name + "!\n You personal info: " + ucManagerInfo.managerInfo(manager)));
    } else {
        info->setText("Error");
    }
    info->update();
}
// TODO why unused?
AddClientsWindow::AddClientsWindow(QWidget *parent) : QWidget(parent) {

    auto *email = new QLabel("Input email:", this);
    email->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *name = new QLabel("Input name:", this);
    name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *phone = new QLabel("Input phone:", this);
    phone->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *deal_product = new QLabel("Input deal_product:", this);
    deal_product->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    email_ = new QLineEdit(this);
    name_ = new QLineEdit(this);
    phone_ = new QLineEdit(this);
    deal_product_ = new QLineEdit(this);

    auto *add_button = new QPushButton("Add", this);

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

void AddClientsWindow::AddClient() {
    UseCaseAddClient ucAddClient(std::make_unique<ClientFileSystem>());
    ucAddClient.addClient({email_->text().toStdString(), name_->text().toStdString(), phone_->text().toStdString(),
                 deal_product_->text().toStdString()}, manager);
    //manager.add_client({email_->text().toStdString(), name_->text().toStdString(), phone_->text().toStdString(),
    //                            deal_product_->text().toStdString()});
    email_->clear();
    name_->clear();
    phone_->clear();
    deal_product_->clear();
    this->close();
}
// TODO why unused?
ClientsList::ClientsList(QWidget *parent) : QWidget(parent) {

    clients_data->setShowGrid(true);
    clients_data->setSelectionMode(QAbstractItemView::SingleSelection);
    clients_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    clients_data->setColumnCount(3);
    clients_data->setHorizontalHeaderLabels(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    if (!manager.name.empty()) {
        this->CreateTable(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    }

    auto *add_client_button = new QPushButton("Add client", this);
    auto *update_button = new QPushButton("Update", this);

    grid = new QGridLayout(this);
    grid->addWidget(clients_data, 0, 0);
    grid->addWidget(add_client_button, 1, 1);
    grid->addWidget(update_button, 1, 2);
    grid = new QGridLayout(this);

    connect(add_client_button, &QPushButton::clicked, this, &ClientsList::OpenAddClientWindow);
    connect(update_button, &QPushButton::clicked, this, &ClientsList::redraw);
}

void ClientsList::OpenAddClientWindow() {
    add_clients_window.show();
}
// TODO clang-tidy, can be const?
void ClientsList::redraw() {
    //CreateTable(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    int t = clients_data->rowCount();

    if (static_cast<int>(manager.listClients.size()) > t) {
        for (; t < static_cast<int>(manager.listClients.size()); t++) {
            clients_data->insertRow(t);
            const people::Client &client = manager.listClients[t];
            clients_data->setItem(t, 0, new QTableWidgetItem(QString::fromStdString(client.email)));
            clients_data->setItem(t, 1, new QTableWidgetItem(QString::fromStdString(client.name)));
            clients_data->setItem(t, 2, new QTableWidgetItem(QString::fromStdString(client.phone)));
        }
    }
    clients_data->update();
}
// TODO clang-tidy, can be const?
void ClientsList::CreateTable(const QStringList &headers) {
    int i = 0;
    clients_data->setHorizontalHeaderLabels(headers);
    for (const people::Client &client : manager.listClients) {
        clients_data->insertRow(i);
        clients_data->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(client.email)));
        clients_data->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(client.name)));
        clients_data->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(client.phone)));
        i++;
    }
    clients_data->resizeColumnsToContents();
}
