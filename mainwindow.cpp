#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow ( QWidget* parent ) :
  QMainWindow ( parent ),
  ui ( new Ui::MainWindow )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  ui->setupUi ( this );
}

MainWindow::~MainWindow()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;

}
