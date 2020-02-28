#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bass.h"


//BASS FX 2.4.12.1 An extension providing several effects, including reverse playback and tempo & pitch


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pd (new PlayersDirector)
{
    ui->setupUi(this);
    RegisterHotKey((HWND)MainWindow::winId(),100,MOD_CONTROL,VK_LEFT );
    RegisterHotKey((HWND)MainWindow::winId(),101,MOD_CONTROL,VK_UP );
    RegisterHotKey((HWND)MainWindow::winId(),102,MOD_CONTROL,VK_DOWN );
    connect (this, SIGNAL(PlayersDirector::volumeChanged(int)), this, SLOT(MainWindow::volumeChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}



bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    MSG* msg = reinterpret_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY){
        switch(msg->wParam){
            case 100:  pd->pause(); break;
            case 101:  pd->volumeUp(); break;
            case 102:  pd->volumeDown(); break;
        }
        return true;
    }
    return false;
}


void MainWindow::on_pushButton_clicked()
{
    pd->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    pd->pause();
}
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    pd->VolumeSliderValueChanged(value);
}
void MainWindow::volumeChanged(int volume){
     ui->horizontalSlider->setValue(volume);
}
