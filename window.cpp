#include "ui_window.h"
#include "window.h"

Window::Window(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui -> setupUi(this);
}

Window::~Window() {
    delete ui;
}

void Window::on_PBTN_REGISTER_clicked() {}
