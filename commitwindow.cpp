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
    QString sql = "INSERT INTO \"transaction\" (hash, message, amount, person) VALUES (?, ?, ?, ?)";
    QString strMsg = ui -> TEDIT_MESSAGE -> toPlainText();
    float amount = ui -> LEDIT_AMOUNT -> text().toFloat();

    QString data = strMsg + ':' + QString::number(amount) + ':' + QString::number(Connx::user.id);

    Connx::queryBinds(sql, QList<QVariant> {Connx::generateHash(data), strMsg, amount, Connx::user.id});
    this -> hide();
}

void CommitWindow::on_PBTN_CANCEL_clicked() {
    this -> hide();
}
