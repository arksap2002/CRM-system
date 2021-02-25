#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTabWidget>

class ErrorWindow : public QWidget {
Q_OBJECT
public:
    [[maybe_unused]] explicit ErrorWindow(QWidget *parent = 0);

    QLabel *errinfo;
}; //окно с сообщением о ошибке

class RegisterWindow : public QWidget {

    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    QString getName();
    QString getPhone();
    QString getEmail();
    QString getLogin();
    QString getPassword();
    QLineEdit *le1;
    QLineEdit *le2;
    QLineEdit *le3;
    QLineEdit *le4;
    QLineEdit *le5;
    ErrorWindow errwind;
private:
    void RegisterManager();
    QLabel *reginfo;

}; //окно регистрации нового пользователя


class GeneralWindow : public QWidget {

public:
    explicit GeneralWindow(QWidget *parent = 0);

};//окно основного взаимодействия

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


class MainWindow : public QTabWidget {
public:
    explicit MainWindow(QWidget *parent = 0);
    void PushLogIn();
    void PushRegister();
}; //главное окно, куда я добавляю все табы, между которыми переключаемся

class StartWindow : public QWidget {

public:
    explicit StartWindow(MainWindow *parent = 0);
    //void LogIn();
    //void Register();
private:
    //LoginWindow log_window;
    //RegisterWindow reg_window;

}; //окно входа

class LoginWindow : public QWidget {

public:
    explicit LoginWindow(MainWindow *parent = 0);
}; //окно где новый пользователь входит в систему

#endif //CRM_SYSTEM_GRAPHICS_H
