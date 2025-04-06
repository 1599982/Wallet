#include "commitwindow.h"
#include "connx/connx.h"
#include "ui_commitwindow.h"

CommitWindow::CommitWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::CommitWindow)
{
    ui -> setupUi(this);
}

CommitWindow::~CommitWindow() {
    delete ui;
}

void CommitWindow::on_PBTN_ACCEPT_clicked() {
    if (Connx::mode == "ADD") {
        addAction();
        return;
    }

    editAction();
}

void CommitWindow::showEvent(QShowEvent *event) {
    if (Connx::mode == "ADD") {
        ui -> TEDIT_MESSAGE -> setText("");
        ui -> LEDIT_AMOUNT -> setText("");
        return;
    }

    sql = "SELECT message, amount FROM \"transaction\" WHERE rowid = ?";
    Connx::result = Connx::queryBinds(sql, QList<QVariant> {Connx::row});

    ui -> TEDIT_MESSAGE -> setText(Connx::result[0].toString());
    ui -> LEDIT_AMOUNT -> setText(Connx::result[1].toString());
};

void CommitWindow::on_PBTN_CANCEL_clicked() {
    this -> hide();
}

void CommitWindow::addAction() {
    sql = "INSERT INTO \"transaction\" (hash, message, amount, person) VALUES (?, ?, ?, ?)";
    QString strMsg = ui -> TEDIT_MESSAGE -> toPlainText();
    float amount = ui -> LEDIT_AMOUNT -> text().toFloat();

    QString data = strMsg + ':' + QString::number(amount) + ':' + QString::number(Connx::user.id);

    Connx::queryBinds(sql, QList<QVariant> {Connx::generateHash(data), strMsg, amount, Connx::user.id});
    this -> hide();
}

void CommitWindow::editAction() {
    sql = "UPDATE \"transaction\" SET hash = ?, message = ?, amount = ? WHERE rowid = ?";
    QString strMsg = ui -> TEDIT_MESSAGE -> toPlainText();
    float amount = ui -> LEDIT_AMOUNT -> text().toFloat();

    QString data = strMsg + ':' + QString::number(amount) + ':' + QString::number(Connx::user.id);

    Connx::queryBinds(sql, QList<QVariant> {Connx::generateHash(data), strMsg, amount, Connx::row});
    this -> hide();
}
