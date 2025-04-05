#ifndef COMMITWINDOW_H
#define COMMITWINDOW_H

#include <QDialog>

namespace Ui {
    class CommitWindow;
}

class CommitWindow: public QDialog {
    Q_OBJECT
public:
    explicit CommitWindow(QWidget *parent = nullptr);
    ~CommitWindow();
private slots:
    void on_PBTN_ACCEPT_clicked();
    void on_PBTN_CANCEL_clicked();
private:
    Ui::CommitWindow *ui;
};

#endif // COMMITWINDOW_H
