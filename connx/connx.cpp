#include "connx.h"
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase ConnX::connect(const QString &dbname) {
    QSqlDatabase qdb = QSqlDatabase::addDatabase("QSQLITE");

    qdb.setDatabaseName(dbname);

    if (qdb.open()) {
        qDebug() << "[Shopify:LOG] database connected :)";
    } else {
        qDebug() << "[Shopify:ERR]" << qdb.lastError();
    }

    QFile file("SQL/main.sql");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "[Shopify:ERR]" << file.errorString();
    }

    QTextStream in(&file);
    QString sqlQuery;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith("--") || line.isEmpty()) {
            continue;
        }

        sqlQuery += line;

        if (line.endsWith(';')) {
            QSqlQuery query(qdb);

            if (!query.exec(sqlQuery)) {
                qDebug() << "[Shopify:ERR]" << query.lastError();
            }

            sqlQuery.clear();
        }
    }

    file.close();

    return qdb;
}
