#include "connx/connx.h"
#include "window.h"
#include <QApplication>

// Person *Connx::user = (Person *) malloc(sizeof(Person));
Person Connx::user = {};

int main(int argc, char *argv[]) {
    QApplication qapp(argc, argv);

    Connx::connect("senati.wallet");

    Window mwdn;
    mwdn.show();

    // free(Connx::user);

    return qapp.exec();
}
