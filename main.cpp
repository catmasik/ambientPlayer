#include "mainwindow.h"
#include <QApplication>
#include "audiothread.h"
#include "playersdirector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QScopedPointer<PlayersDirector> pd ( new PlayersDirector () );

    pd->createPlayers();
    pd->play();

    //auto* audio_thread1 = new AudioThread;
    //audio_thread1->play("c:/Downloads/english.mp3");

    /*auto* audio_thread2 = new AudioThread;
    audio_thread2->audio_thread_cfg.audio_file_path = "h:/QT/MyProjects/TEST1/tick.mp3";
    audio_thread2->play();*/

    /*auto* audio_thread3 = new AudioThread;
    audio_thread3->play("h:/Music/20356.mp3");
    auto* audio_thread4 = new AudioThread;
    audio_thread4->play("h:/Music/49162cd6f35c4f.mp3");
    auto* audio_thread5 = new AudioThread;
    audio_thread5->play("h:/Music/64274.mp3");*/
    return a.exec();
}
