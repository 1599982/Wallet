#include "ui_window.h"
#include "window.h"
#include <QSqlError>
#include <QSqlQuery>

Window::Window(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui -> setupUi(this);
}

Window::~Window() {
    delete ui;
}

void Window::on_PBTN_LOGIN_clicked() {
    QString strUser = ui -> LEDIT_USER -> text();
    QString strPass = ui -> LEDIT_PASS -> text();
}

void Window::on_PBTN_REGISTER_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_REGISTER);
}

void Window::on_PBTN_REGISTER_R_clicked() {
    QString strUser = ui -> LEDIT_USER_R -> text();
    QString strPass = ui -> LEDIT_PASS_R -> text();
    QString strRePass = ui -> LEDIT_REPASS_R -> text();

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM person WHERE user = ?");
    query.addBindValue(strUser);
    query.exec();
    query.next();

    bool exist = query.value(0).toBool();

    if (exist) {
        qDebug() << "[Wallet:ERR] ...";
        return;
    }

    if (strPass.compare(strRePass) != 0) {
        qDebug() << "[Wallet:ERR] ...";
        return;
    }

    query.prepare("INSERT INTO person (user, pass) VALUES (?, ?)");
    query.addBindValue(strUser);
    query.addBindValue(strPass);
    query.exec();
}

void Window::on_PBTN_CANCEL_R_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_LOGIN);
}
