#ifndef CONNX_H
#define CONNX_H

#include <QSqlDatabase>
#include <QString>

struct Person {
    QString session;
    int id;
    QString name;
};

namespace Connx {
    extern Person user;
    QSqlDatabase connect();
    void connect(const QString &dbname);

    // Util
    QString generateHash(QString &data);
    bool userExists(const QString &username);
    QVariant queryBinds(const QString &sql, const QVariant &bind);
    QList<QVariant> queryBinds(const QString &sql, const QList<QVariant> &binds);
}

#endif // CONNX_H
