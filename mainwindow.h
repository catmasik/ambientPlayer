#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "playersdirector.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QScopedPointer<PlayersDirector> pd;
};

#endif // MAINWINDOW_H
