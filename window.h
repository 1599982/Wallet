#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Window;
}
QT_END_NAMESPACE

class Window: public QMainWindow {
    Q_OBJECT
public:
    QSqlDatabase db;

    Window(QWidget *parent = nullptr);
    ~Window();
private slots:
    void on_PBTN_LOGIN_clicked();
    void on_PBTN_REGISTER_clicked();
    void on_PBTN_REGISTER_R_clicked();
    void on_PBTN_CANCEL_R_clicked();
private:
    Ui::Window *ui;
};

#endif // WINDOW_H
