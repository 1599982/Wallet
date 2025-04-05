#ifndef CONNX_H
#define CONNX_H

#include <QSqlDatabase>
#include <QString>

namespace Connx {
    QSqlDatabase connect();
    void connect(const QString &dbname);

    // Util
    bool userExists(const QString &username);
    QVariant queryBinds(const QString &sql, const QVariant &bind);
    QList<QVariant> queryBinds(const QString &sql, const QList<QVariant> &binds);
}

#endif // CONNX_H
