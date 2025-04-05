#include "connx.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

QSqlDatabase Connx::connect() {
    return QSqlDatabase::database();
}

void Connx::connect(const QString &dbname) {
    QSqlDatabase qdb = QSqlDatabase::addDatabase("QSQLITE");
    qdb.setConnectOptions("QSQLITE_BUSY_TIMEOUT=5000");
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

QString Connx::generateHash(QString &data) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    data = currentDate.toString("yyyy-MM-dd") + ':' + currentTime.toString("HH:mm:ss") + ':' + data;

    QByteArray byteArray = data.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha1);

    return hash.toHex();
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

    while (query.next()) {
        for (int i = 0; i < query.record().count(); ++i) {
            results.append(query.value(i));
        }
    }

    return results;
}
