#ifndef WINDOW_H
#define WINDOW_H

#include "commitwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Window;
}
QT_END_NAMESPACE

class Window: public QMainWindow {
    Q_OBJECT
public:
    Window(QWidget *parent = nullptr);
    ~Window();
private slots:
    void on_PBTN_LOGIN_clicked();
    void on_PBTN_REGISTER_clicked();
    void on_PBTN_REGISTER_R_clicked();
    void on_PBTN_CANCEL_R_clicked();
    void on_PBTN_ADD_clicked();
    void on_PBTN_EDIT_clicked();
    void on_PBTN_UPDATE_clicked();
private:
    Ui::Window *ui;
    CommitWindow *cmwdn;

    void updateTable();
};

#endif // WINDOW_H
