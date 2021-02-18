#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class ErrorWindow : public QWidget {

    explicit ErrorWindow(QWidget *parent = 0);
Q_OBJECT

    QLabel *errinfo;
};

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
private:
    void RegisterManager();
    QLabel *reginfo;

};

class LoginWindow : public QWidget {

public:
    explicit LoginWindow(QWidget *parent = 0);
};

class Application : public QWidget {

//Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);

private:
    void LogIn();
    void Register();
    LoginWindow log_window;
    RegisterWindow reg_window;

};

#endif //CRM_SYSTEM_GRAPHICS_H
