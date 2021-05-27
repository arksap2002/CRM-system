#include "graphics.h"
#include "CRM-system_client.h"
#include "storage.h"
#include "storageFileSystem.h"
#include "useCases.h"

using namespace people;
using namespace repositories;
using namespace useCases;

enum Windows {
    start_window_num = 0,
    login_window_num = 1,
    registration_window_num = 2,
    general_window_num = 3,
    info_window_num = 4,
    clients_list_window_num = 5,
    add_clients_window_num = 6,
};

people::Manager manager = people::Manager();

void redraw(QWidget *page) {

    if (auto *d = dynamic_cast<GeneralWindow *>(page); d != nullptr) {
        if (!manager.name.empty()) {
            d->manager_name->setText(QString::fromStdString(
                    "Hello, " + manager.name + "! Here is a general window. Here are some options:"));
            d->manager_name->update();
        }
    } else if (auto *k = dynamic_cast<ManagersWindow *>(page); k != nullptr) {
        UseCaseManagerInfo ucManagerInfo(std::make_unique<ManagerFileSystem>());
        if (!manager.name.empty()) {
            k->info->setText(
                    QString::fromStdString(
                            "Hello " + manager.name + "!\n You personal info: " + ucManagerInfo.managerInfo(manager)));
        } else {
            k->info->setText("Error");
        }
        k->info->update();
    } else if (auto *v = dynamic_cast<ClientsList *>(page); v != nullptr) {
        int i = 0;
        v->clients_data->clearContents();
        v->clients_data->model()->removeRows(0, v->clients_data->rowCount());
        v->clients_data->setRowCount(0);
        for (const people::Client &client : manager.listClients) {
            v->clients_data->insertRow(i);
            v->clients_data->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(client.email)));
            v->clients_data->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(client.name)));
            v->clients_data->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(client.phone)));
            i++;
        }
        v->clients_data->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        v->clients_data->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        v->clients_data->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    }
}

ErrorWindow::ErrorWindow(QWidget *parent) : QWidget(parent) {

    errinfo = new QLabel("Error", this);

    auto *grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);
    grid->addWidget(errinfo);
    setLayout(grid);
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
    register_button->setShortcut(Qt::Key_Return);

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
    QString name = name_->text();
    name_->clear();
    return name;
}

QString RegisterWindow::getPhone() const {
    QString phone = phone_->text();
    phone_->clear();
    return phone;
}

QString RegisterWindow::getEmail() const {
    QString email = email_->text();
    email_->clear();
    return email;
}

QString RegisterWindow::getPassword() const {
    QString pass = password_->text();
    password_->clear();
    return pass;
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
    login_button->setShortcut(Qt::Key_Return);

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
    QString email = email_->text();
    email_->clear();
    return email;
}

QString LoginWindow::getPassword() const {
    QString pass = password_->text();
    password_->clear();
    return pass;
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
}

void MainWindow::ChangeToStart() const {
    stackedWidget->setCurrentIndex(start_window_num);
}

void MainWindow::ChangeToLogIn() const {
    stackedWidget->setCurrentIndex(login_window_num);
}

void MainWindow::ChangeToRegister() const {
    stackedWidget->setCurrentIndex(registration_window_num);
}

void MainWindow::ChangeToGeneral() const {
    ::redraw(stackedWidget->widget(general_window_num));
    stackedWidget->setCurrentIndex(general_window_num);
}

void MainWindow::ChangeToInfo() const {
    ::redraw(stackedWidget->widget(info_window_num));
    stackedWidget->setCurrentIndex(info_window_num);
}

void MainWindow::ChangeToClientsList() const {
    ::redraw(stackedWidget->widget(clients_list_window_num));
    stackedWidget->setCurrentIndex(clients_list_window_num);
}

void MainWindow::ChangeToAddClients() const {
    stackedWidget->setCurrentIndex(add_clients_window_num);
}

void MainWindow::SetManager(const people::Manager &manager_) {
    manager = manager_;
}

GeneralWindow::GeneralWindow(MainWindow *parent) : QWidget(parent) {

    parent->stackedWidget->addWidget(this);

    if (manager.name.empty()) {
        manager_name = new QLabel("error. need to update", this);
    } else {
        manager_name = new QLabel(QString::fromStdString(manager.name), this);
    }

    auto *managers_window_button = new QPushButton("Open managers window", this);
    auto *clients_list_button = new QPushButton("Open clients list", this);
    auto *exit_button = new QPushButton("Log out", this);

    grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);

    grid->addWidget(manager_name, 0, 0);
    grid->addWidget(managers_window_button, 1, 0);
    grid->addWidget(clients_list_button, 2, 0);
    grid->addWidget(exit_button, 3, 0);

    setLayout(grid);

    connect(managers_window_button, &QPushButton::clicked, parent, &MainWindow::ChangeToInfo);
    connect(clients_list_button, &QPushButton::clicked, parent, &MainWindow::ChangeToClientsList);
    connect(exit_button, &QPushButton::clicked, parent, &MainWindow::ChangeToStart);
}

ManagersWindow::ManagersWindow(MainWindow *parent) : QWidget(parent) {

    parent->stackedWidget->addWidget(this);
    UseCaseManagerInfo ucManagerInfo(std::make_unique<ManagerDataBase_client>());

    if (!ucManagerInfo.managerInfo(manager).empty()) {
        info = new QLabel(
                QString::fromStdString(
                        "Hello" + manager.name + "!\n You personal info: " + ucManagerInfo.managerInfo(manager)),
                this);
    } else {
        info = new QLabel("No manager. Error", this);
    }

    auto *exit_button = new QPushButton("Exit", this);

    auto *grid = new QGridLayout(this);
    grid->setVerticalSpacing(40);
    grid->setHorizontalSpacing(10);
    grid->addWidget(info, 0, 0);
    grid->addWidget(exit_button, 2, 1);
    setLayout(grid);

    connect(exit_button, &QPushButton::clicked, parent, &MainWindow::ChangeToGeneral);
}

AddClientsWindow::AddClientsWindow(MainWindow *parent) : QWidget(parent) {

    parent->stackedWidget->addWidget(this);

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
    auto *exit_button = new QPushButton("Exit", this);

    auto *grid = new QGridLayout(this);

    grid->setVerticalSpacing(20);
    grid->setHorizontalSpacing(10);

    grid->addWidget(email, 1, 0);
    grid->addWidget(email_, 1, 1);
    grid->addWidget(name, 2, 0);
    grid->addWidget(name_, 2, 1);
    grid->addWidget(phone, 3, 0);
    grid->addWidget(phone_, 3, 1);
    grid->addWidget(deal_product, 4, 0);
    grid->addWidget(deal_product_, 4, 1);
    grid->addWidget(add_button, 5, 1);
    grid->addWidget(exit_button, 5, 2);

    setLayout(grid);

    connect(add_button, &QPushButton::clicked, this, &AddClientsWindow::AddClient);
    connect(exit_button, &QPushButton::clicked, parent, &MainWindow::ChangeToClientsList);
}

void AddClientsWindow::AddClient() const {

    UseCaseAddClient ucAddClient(std::make_unique<ClientDataBase_client>());
    ucAddClient.addClient({email_->text().toStdString(), name_->text().toStdString(), phone_->text().toStdString(),
                           deal_product_->text().toStdString()},
                          manager);

    email_->clear();
    name_->clear();
    phone_->clear();
    deal_product_->clear();

}

ClientsList::ClientsList(MainWindow *parent) : QWidget(parent) {

    parent->stackedWidget->addWidget(this);

    clients_data->setShowGrid(true);
    clients_data->setSelectionMode(QAbstractItemView::SingleSelection);
    clients_data->setSelectionBehavior(QAbstractItemView::SelectRows);
    clients_data->setColumnCount(3);
    clients_data->setHorizontalHeaderLabels(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    if (!manager.name.empty()) {
        this->CreateTable(QStringList() << trUtf8("email") << trUtf8("name") << trUtf8("phone"));
    }
    clients_data->setEditTriggers(QAbstractItemView::NoEditTriggers);

    auto *add_client_button = new QPushButton("Add client", this);
    auto *exit_button = new QPushButton("Exit", this);

    grid = new QGridLayout(this);
    grid->addWidget(clients_data, 0, 0);
    grid->addWidget(add_client_button, 1, 1);
    grid->addWidget(exit_button, 1, 2);
    setLayout(grid);

    connect(add_client_button, &QPushButton::clicked, parent, &MainWindow::ChangeToAddClients);
    connect(exit_button, &QPushButton::clicked, parent, &MainWindow::ChangeToGeneral);
    connect(clients_data, &QTableWidget::doubleClicked,
            this, &ClientsList::OpenClientsWindow);
}

void ClientsList::OpenClientsWindow(const QModelIndex &index) {
    int row = index.row();
    QString email = clients_data->item(row, 0)->text();
    QString name = clients_data->item(row, 1)->text();
    QString phone = clients_data->item(row, 2)->text();
    auto *wind = new ClientsWindow;
    wind->SetInfo(name, email, phone);
    wind->resize(500, 500);
    wind->setWindowTitle("Clients info");
    wind->show();
}

void ClientsList::CreateTable(const QStringList &headers) const {
    int i = 0;
    clients_data->setHorizontalHeaderLabels(headers);
    for (const people::Client &client : manager.listClients) {
        clients_data->insertRow(i);
        clients_data->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(client.email)));
        clients_data->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(client.name)));
        clients_data->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(client.phone)));
        i++;
    }
    clients_data->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    clients_data->resizeColumnsToContents();
}

ClientsWindow::ClientsWindow(MainWindow *parent) : QWidget(parent) {

    info = new QLabel(QString::fromStdString("Clients info:"), this);
    auto *delete_button = new QPushButton("Delete this client", this);

    auto *grid = new QGridLayout(this);
    grid->addWidget(info, 0, 0);
    grid->addWidget(delete_button, 1, 0);
    setLayout(grid);

    connect(delete_button, &QPushButton::clicked, this, &ClientsWindow::DeleteClient);
}

void ClientsWindow::SetInfo(const QString &name, const QString &email, const QString &phone) {
    info->setText(QString::fromStdString("Clients info:\nName: ") + name +
                  QString::fromStdString("\nEmail: ") + email +
                  QString::fromStdString("\nPhone: ") + phone);
    clients_email = email;
}


void ClientsWindow::DeleteClient() {
    UseCaseDeleteClient ucDeleteClient(std::make_unique<ClientFileSystem>());
    ucDeleteClient.deleteClient(clients_email.toStdString(), manager.email);
    this->close();
    /*UseCaseDeleteClient ucDeleteClient(unique_ptr<ClientFileSystem>()
    ucDeleteClient.deleteClient(clientEmail, managerEmail)*/
}