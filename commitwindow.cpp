#include "commitwindow.h"
#include "connx/connx.h"
#include "ui_commitwindow.h"
// #include <QSqlQuery>

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
    QString sql = "INSERT INTO \"transaction\" (hash, message, amount, person) VALUES (\"eec25a0b\", ?, ?, ?)";
    QString strMsg = ui -> TEDIT_MESSAGE -> toPlainText();
    float amount = ui -> LEDIT_AMOUNT -> text().toFloat();

    Connx::queryBinds(sql, QList<QVariant> {strMsg, amount, 1});
}
