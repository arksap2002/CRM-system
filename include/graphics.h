#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>
#include <QGridLayout>
#include "people.h"

class ErrorWindow : public QWidget {
Q_OBJECT
public:
    [[maybe_unused]] explicit ErrorWindow(QWidget *parent = 0);

    QLabel *errinfo;
}; //окно с сообщением о ошибке


class AddClientsWindow : public QWidget {

public:
    explicit AddClientsWindow(QWidget *parent = 0);

};//окно добавления клиента

class ManagersWindow : public QWidget {

public:
    explicit ManagersWindow(QWidget *parent = 0);

};//окно менеджера загадка что там и как оно достигается

class ClientsList : public QWidget {

public:
    explicit ClientsList(QWidget *parent = 0);

};//окно со списком клиентов

class GeneralWindow : public QWidget {
Q_OBJECT
    //MainWindow *mainwind;
public:
    people::Manager *manager = nullptr;
    explicit GeneralWindow(QWidget *parent = 0, people::Manager *manager_ = nullptr);
    QLabel *manager_name;
    void redraw();
    QGridLayout *grid;

    void SetManager(people::Manager &manager);


};//окно основного взаимодействия

class MainWindow : public QTabWidget {
public:
    people::Manager *manager = nullptr;
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