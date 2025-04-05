#include "commitwindow.h"
#include "connx/connx.h"
#include "ui_window.h"
#include "window.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

QString sql;

Window::Window(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui -> setupUi(this);
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_LOGIN);
}

Window::~Window() {
    delete ui;
}

void Window::on_PBTN_LOGIN_clicked() {
    QString strUser = ui -> LEDIT_USER -> text();
    QString strPass = ui -> LEDIT_PASS -> text();

    if (!Connx::userExists(strUser)) {
        qDebug() << "[window:ERR] Window::on_PBTN_LOGIN_clicked :-: 1";
        return;
    }

    sql = "SELECT pass FROM person WHERE user = ?";
    QString pass = Connx::queryBinds(sql, strUser).toString();

    if (strPass.compare(pass) != 0) {
        qDebug() << "[window:ERR] Window::on_PBTN_LOGIN_clicked() :-: 2";
        return;
    }

    sql = "SELECT * FROM person WHERE user = ?";
    QList<QVariant> person = Connx::queryBinds(sql, QList<QVariant> {strUser});

    QString data = person[0].toString() + ':' + person[1].toString();
    Connx::user.session = Connx::generateHash(data);
    Connx::user.id = person[0].toInt();
    Connx::user.name = person[1].toString();

    sql = "SELECT trs.hash, trs.date, trs.time, trs.message, trs.amount, person.user FROM \"transaction\" AS trs JOIN person ON trs.person = person.id";
    QSqlQueryModel *model = new QSqlQueryModel();
    model -> setQuery(sql, Connx::connect());

    if (model -> lastError().isValid()) {
        qDebug() << "[window::ERR]" << model -> lastError();
    }

    ui -> TBV_TRANS -> setModel(model);
    // ui -> TBV_TRANS -> verticalHeader() -> setVisible(false);
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_MAIN);
}

void Window::on_PBTN_REGISTER_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_REGISTER);
}

void Window::on_PBTN_REGISTER_R_clicked() {
    QString strUser = ui -> LEDIT_USER_R -> text();
    QString strPass = ui -> LEDIT_PASS_R -> text();
    QString strRePass = ui -> LEDIT_REPASS_R -> text();

    if (Connx::userExists(strUser)) {
        qDebug() << "[window:ERR] Window::on_PBTN_REGISTER_R_clicked() :-: 1";
        return;
    }

    if (strPass.compare(strRePass) != 0) {
        qDebug() << "[window:ERR] Window::on_PBTN_REGISTER_R_clicked() :-: 2";
        return;
    }

    sql = "INSERT INTO person (user, pass) VALUES (?, ?)";
    Connx::queryBinds(sql, QList<QVariant> {strUser, strPass});
}

void Window::on_PBTN_CANCEL_R_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_LOGIN);
}

void Window::on_PBTN_ADD_clicked() {
    CommitWindow *cmwdn = new CommitWindow();
    cmwdn -> setModal(true);
    cmwdn -> show();
}
