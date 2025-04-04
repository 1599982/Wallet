#include "connx/connx.h"
#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication qapp(argc, argv);

    QSqlDatabase db = ConnX::connect("senati.wallet");

    Window mwdn;
    mwdn.show();

    db.close();

    return qapp.exec();
}
