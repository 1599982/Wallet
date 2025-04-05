#include "connx/connx.h"
#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication qapp(argc, argv);

    Connx::connect("senati.wallet");

    Window mwdn;
    mwdn.show();

    return qapp.exec();
}
