#include "commitwindow.h"
#include "connx/connx.h"
#include "ui_window.h"
#include "window.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTimer>

// QString sql;

QList<QVariant> Connx::result;
int Connx::row = -1;
QString Connx::mode = "";

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

    Window::updateTable();

    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_MAIN);
}

void Window::on_PBTN_REGISTER_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_REGISTER);
}

void Window::on_PBTN_REGISTER_R_clicked() {
    QString strUser = ui -> LEDIT_USER_R -> text();
    QString strPass = ui -> LEDIT_PASS_R -> text();
    QString strRePass = ui -> LEDIT_REPASS_R -> text();

    if (strUser.isEmpty() || strPass.isEmpty() || strRePass.isEmpty()) {
        qDebug() << "[window:ERR] Window::on_PBTN_REGISTER_R_clicked() :-: 1";
        return;
    }

    if (Connx::userExists(strUser)) {
        qDebug() << "[window:ERR] Window::on_PBTN_REGISTER_R_clicked() :-: 2";
        return;
    }

    if (strPass.compare(strRePass) != 0) {
        qDebug() << "[window:ERR] Window::on_PBTN_REGISTER_R_clicked() :-: 3";
        return;
    }

    sql = "INSERT INTO person (user, pass) VALUES (?, ?)";
    Connx::queryBinds(sql, QList<QVariant> {strUser, strPass});
}

void Window::on_PBTN_CANCEL_R_clicked() {
    ui -> STKW_FORM -> setCurrentWidget(ui -> STKW_FORM_LOGIN);
}

void Window::on_PBTN_ADD_clicked() {
    Connx::mode = "ADD";
    cmwdn = new CommitWindow();
    cmwdn -> setModal(true);
    cmwdn -> show();
}

void Window::on_PBTN_EDIT_clicked() {
    Connx::mode = "EDIT";
    Connx::row = ui -> TBV_TRANS -> currentIndex().row() + 1;

    sql = "SELECT person FROM \"transaction\" WHERE rowid = ?";
    int user = Connx::queryBinds(sql, Connx::row).toInt();

    qDebug() << user << Connx::user.id;

    if (user != Connx::user.id) {
        qDebug() << "[window:ERR] Window::on_PBTN_EDIT_clicked() :-: 1";
        return;
    }

    cmwdn = new CommitWindow();
    cmwdn -> setModal(true);
    cmwdn -> show();
}

void Window::on_PBTN_UPDATE_clicked() {
    Window::updateTable();
}

void Window::updateTable() {
    sql = "SELECT trs.hash, trs.date, trs.time, trs.message, trs.amount, person.user FROM \"transaction\" AS trs JOIN person ON trs.person = person.id";
    QSqlQueryModel *model = new QSqlQueryModel();

    if (model -> lastError().isValid()) {
        qDebug() << "[window::ERR]" << model -> lastError();
    }

    // QTimer *timer = new QTimer(this);
    model -> setQuery(sql, Connx::connect());
    ui -> TBV_TRANS -> setModel(model);

    // connect(timer, &QTimer::timeout, this, [=]() {
    //     model -> setQuery(sql, Connx::connect());

    //     if (Connx::row != -1) {
    //         ui -> TBV_TRANS -> selectRow(Connx::row);
    //     }
    // });

    // timer -> start(2000);
}
