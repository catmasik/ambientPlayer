#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMediaPlayer>

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

private:
    Ui::MainWindow *ui;
};


struct ctms_audio_stream
{
    QString audio_file_path;  // путь к аудиофайлу
    int repeatability;  //( 0 - бесконечно, 1- 1 раз и тд.  )
    int first_delay;    //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
    int delay;         //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
    int volume;       //  громкость (0-100)
    QMediaPlayer *player;
};


#endif // MAINWINDOW_H
