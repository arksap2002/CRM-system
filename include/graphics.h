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
#include <QStackedWidget>

void redraw(QWidget *page);

class MainWindow : public QWidget {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QStackedWidget *stackedWidget = new QStackedWidget;
    void ChangeToStart() const;
    void ChangeToLogIn() const;
    void ChangeToRegister() const;
    void ChangeToGeneral() const;
    void ChangeToInfo() const;
    void ChangeToClientsList() const;
    void ChangeToAddClients() const;
    void SetManager(const people::Manager &);
    //GeneralWindow general_window;
};//главное окно, куда я добавляю в стек все окна

class ErrorWindow : public QWidget {
    Q_OBJECT
public:
    [[maybe_unused]] explicit ErrorWindow(QWidget *parent = nullptr);
    QLabel *errinfo;
};//окно с сообщением о ошибке

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
    ErrorWindow error_window_login;
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
    ErrorWindow error_window_register;

private:
    void RegisterManager();
    QLabel *reginfo;

};//окно регистрации нового пользователя

class AddClientsWindow : public QWidget {

public:
    explicit AddClientsWindow(MainWindow *parent = nullptr);
    void AddClient() const;
    QLineEdit *email_;
    QLineEdit *phone_;
    QLineEdit *name_;
    QLineEdit *deal_product_;

};//окно добавления клиента

class ClientsList : public QWidget {

public:
    explicit ClientsList(MainWindow *parent = nullptr);
    //AddClientsWindow add_clients_window;
    QGridLayout *grid;
    QTableWidget *clients_data = new QTableWidget(this);
    void CreateTable(const QStringList &headers) const;

};//окно со списком клиентов


class ManagersWindow : public QWidget {
    Q_OBJECT

public:
    QGridLayout *grid;
    QLabel *info;
    explicit ManagersWindow(MainWindow *parent = nullptr);

};//окно менеджера загадка что там и как оно достигается


class GeneralWindow : public QWidget {
    Q_OBJECT

public:
    explicit GeneralWindow(MainWindow *parent = nullptr);
    QLabel *manager_name;
    QGridLayout *grid;

};//окно основного взаимодействия


#endif//CRM_SYSTEM_GRAPHICS_H
