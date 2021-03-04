#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include "people.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QWidget>


class ErrorWindow : public QWidget {
    Q_OBJECT
public:
    [[maybe_unused]] explicit ErrorWindow(QWidget *parent = nullptr);

    QLabel *errinfo;
};//окно с сообщением о ошибке

class AddClientsWindow : public QWidget {

public:
    explicit AddClientsWindow(QWidget *parent = nullptr);
    void AddClient();
    QLineEdit *email_;
    QLineEdit *phone_;
    QLineEdit *name_;
    QLineEdit *deal_product_;

};//окно добавления клиента

class ClientsList : public QWidget {

public:
    explicit ClientsList(QWidget *parent = nullptr);
    AddClientsWindow add_clients_window;
    QGridLayout *grid;
    QTableWidget *clients_data = new QTableWidget(this);
    void CreateTable(const QStringList &headers);
    void redraw();
    void OpenAddClientWindow();

};//окно со списком клиентов


class ManagersWindow : public QWidget {
    Q_OBJECT

public:
    QGridLayout *grid;
    QLabel *info;
    explicit ManagersWindow(QWidget *parent = nullptr);
    void redraw();

};//окно менеджера загадка что там и как оно достигается


class GeneralWindow : public QWidget {
    Q_OBJECT

public:
    explicit GeneralWindow(QWidget *parent = nullptr);
    QLabel *manager_name;
    QGridLayout *grid;
    ManagersWindow managers_window;
    ClientsList clients_window;

    void redraw();
    void OpenManagersAccount();
    void OpenClientsWindow();

};//окно основного взаимодействия

class MainWindow : public QTabWidget {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void ChangeToStart();
    void ChangeToLogIn();
    void ChangeToRegister();
    void ChangeToGeneral();
    void ChangeToClients();
    void SetManager(const people::Manager &);
    GeneralWindow general_window;
};//главное окно, куда я добавляю все табы, между которыми переключаемся

class StartWindow : public QWidget {

public:
    explicit StartWindow(MainWindow *parent = nullptr);

};//окно входа

class LoginWindow : public QWidget {
    MainWindow *mainwind;
    Q_OBJECT
public:
    explicit LoginWindow(MainWindow *parent = nullptr);
    [[nodiscard]] QString getEmail() const;
    [[nodiscard]] QString getPassword() const;
    QLineEdit *email_;
    QLineEdit *password_;
    QLabel *logininfo;
    void LoginManager();
};//окно где новый пользователь входит в систему

class RegisterWindow : public QWidget {
    Q_OBJECT

    MainWindow *mainwind;

public:
    explicit RegisterWindow(MainWindow *parent = nullptr);
    [[nodiscard]] QString getName() const;
    [[nodiscard]] QString getPhone() const;
    [[nodiscard]] QString getEmail() const;
    [[nodiscard]] QString getPassword() const;
    QLineEdit *email_;
    QLineEdit *name_;
    QLineEdit *phone_;
    QLineEdit *password_;
    ErrorWindow errwind;

private:
    void RegisterManager();
    QLabel *reginfo;

};//окно регистрации нового пользователя

#endif//CRM_SYSTEM_GRAPHICS_H
