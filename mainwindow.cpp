#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bass.h"

//BASS FX 2.4.12.1 An extension providing several effects, including reverse playback and tempo & pitch


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*BASS_Init (-1, 44100, 0, 0, NULL);
    DWORD stream;
    char filename[] = "c:/Downloads/english.mp3";
    stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0);
    BASS_DX8_DISTORTION* distortion = new BASS_DX8_DISTORTION();
    int fxHandle = BASS_ChannelSetFX(stream, BASS_FX_DX8_DISTORTION, 0);
    BASS_FXSetParameters(fxHandle, distortion);
    BASS_ChannelPlay(stream,TRUE);*/


}

MainWindow::~MainWindow()
{
    delete ui;
}
