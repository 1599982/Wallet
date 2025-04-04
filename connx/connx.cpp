#include "connx.h"
#include <QSqlError>

QSqlDatabase ConnX::connect(const QString &dbname) {
    QSqlDatabase qdb = QSqlDatabase::addDatabase("QSQLITE");

    qdb.setDatabaseName(dbname);

    if (qdb.open()) {
        qDebug() << "[Shopify:LOG] database connected :)";
    } else {
        qDebug() << "[Shopify:ERR]" << qdb.lastError();
    }

    return qdb;
}
