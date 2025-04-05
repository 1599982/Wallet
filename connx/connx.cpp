#include "connx.h"
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

QSqlDatabase Connx::connect() {
    return QSqlDatabase::database();
}

void Connx::connect(const QString &dbname) {
    QSqlDatabase qdb = QSqlDatabase::addDatabase("QSQLITE");
    qdb.setDatabaseName(dbname);

    if (qdb.open()) {
        qDebug() << "[connx:LOG] database connected :)";
    } else {
        qDebug() << "[connx:ERR]" << qdb.lastError();
    }

    QFile file("SQL/main.sql");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "[connx:ERR]" << file.errorString();
    }

    QTextStream in(&file);
    QString strQuery;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith("--") || line.isEmpty()) {
            continue;
        }

        strQuery += line;

        if (line.endsWith(';')) {
            QSqlQuery query(qdb);

            if (!query.exec(strQuery)) {
                qDebug() << "[connx:ERR]" << query.lastError();
            }

            strQuery.clear();
        }
    }

    file.close();
}

bool Connx::userExists(const QString &username) {
    QString sql = "SELECT COUNT(*) FROM person WHERE user = ?";
    return Connx::queryBinds(sql, username).toBool();
}

QVariant Connx::queryBinds(const QString &sql, const QVariant &bind) {
    QSqlQuery query(sql);
    query.addBindValue(bind);
    query.exec();
    query.next();

    return query.value(0);
}

QList<QVariant> Connx::queryBinds(const QString &sql, const QList<QVariant> &binds) {
    QList<QVariant> results;
    QSqlQuery query(sql);

    for (const auto &bn : binds) {
        query.addBindValue(bn);
    }

    if (!query.exec()) {
        qDebug() << "[connx::ERR]" << query.lastError();
    }

    int i = 0;

    while (query.next()) {
        results.append(query.value(i));
        i++;
    }

    return results;
}
