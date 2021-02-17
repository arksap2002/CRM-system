#ifndef CRM_SYSTEM_GRAPHICS_H
#define CRM_SYSTEM_GRAPHICS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class RegisterWindow : public QWidget {

public:
    explicit RegisterWindow(QWidget *parent = 0);
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

};

#endif //CRM_SYSTEM_GRAPHICS_H
