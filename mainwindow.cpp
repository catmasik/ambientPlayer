#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QDir>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

   /* QMediaPlayer *player = nullptr;
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("c:/Downloads/5844_Raim_Davletyaro.mp3"));
    player->setVolume(50);
    player->play();*/


}
