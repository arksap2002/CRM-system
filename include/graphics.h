#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <QGridLayout>
#include <QTableWidget>
#include "people.h"


class ErrorWindow : public QWidget {
Q_OBJECT
public:
    [[maybe_unused]] explicit ErrorWindow(QWidget *parent = 0);

    QLabel *errinfo;
}; //окно с сообщением о ошибке

class AddClientsWindow : public QWidget {

public:
    people::Manager manager;
    explicit AddClientsWindow(QWidget *parent = 0);
    void SetManager(people::Manager *manager_);
    void AddClient();
    QLineEdit *email_;
    QLineEdit *phone_;
    QLineEdit *name_;
    QLineEdit *deal_product_;

};//окно добавления клиента

class ClientsList : public QWidget {
    people::Manager manager;
public:
    explicit ClientsList(QWidget *parent = 0);
    AddClientsWindow add_clients_window;
    QGridLayout *grid;
    QTableWidget *clients_data = new QTableWidget(this);
    void SetManager(people::Manager &manager_);
    void CreateTable(const QStringList &headers);
    void redraw();
    void OpenAddClientWindow();

};//окно со списком клиентов


class ManagersWindow : public QWidget {
Q_OBJECT
    people::Manager manager;
public:
    QGridLayout *grid;
    QLabel *info;
    explicit ManagersWindow(QWidget *parent = 0, people::Manager manager = people::Manager());
    void SetManager(people::Manager &manager_);
    void redraw();

};//окно менеджера загадка что там и как оно достигается


class GeneralWindow : public QWidget {
Q_OBJECT

public:
    people::Manager manager = people::Manager();
    explicit GeneralWindow(QWidget *parent = 0, people::Manager manager_ = people::Manager());
    QLabel *manager_name;
    QGridLayout *grid;
    ManagersWindow managers_window;
    ClientsList clients_window;

    void redraw();
    void SetManager(people::Manager &manager);
    people::Manager& GetManager();
    void OpenManagersAccount();
    void OpenClientsWindow();

};//окно основного взаимодействия

class MainWindow : public QTabWidget {
public:
    people::Manager manager = people::Manager();
    explicit MainWindow(QWidget *parent = 0);
    void ChangeToStart();
    void ChangeToLogIn();
    void ChangeToRegister();
    void ChangeToGeneral();
    void ChangeToClients();
    people::Manager& GetManager();
    void SetManager(people::Manager &manager_);
    GeneralWindow general_window;
}; //главное окно, куда я добавляю все табы, между которыми переключаемся

class StartWindow : public QWidget {

public:
    explicit StartWindow(MainWindow *parent = 0);

}; //окно входа

class LoginWindow : public QWidget {
    MainWindow *mainwind;
Q_OBJECT
public:
    explicit LoginWindow(MainWindow *parent = 0);
    QString getEmail();
    QString getPassword();
    QLineEdit *email_;
    QLineEdit *password_;
    QLabel *logininfo;
    void LoginManager();
}; //окно где новый пользователь входит в систему

class RegisterWindow : public QWidget {
Q_OBJECT

    MainWindow *mainwind;

public:
    explicit RegisterWindow(MainWindow *parent = 0);
    QString getName();
    QString getPhone();
    QString getEmail();
    QString getPassword();
    QLineEdit *email_;
    QLineEdit *name_;
    QLineEdit *phone_;
    QLineEdit *password_;
    ErrorWindow errwind;
private:
    void RegisterManager();
    QLabel *reginfo;

}; //окно регистрации нового пользователя

#endif //CRM_SYSTEM_GRAPHICS_H