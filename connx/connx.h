#ifndef CONNX_H
#define CONNX_H

#include <QSqlDatabase>

namespace ConnX {
    QSqlDatabase connect(const QString &dbname);
}

#endif // CONNX_H
