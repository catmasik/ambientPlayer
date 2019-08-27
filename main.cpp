#include "mainwindow.h"
#include "playersdirector.h"
#include <QApplication>

#include <QTimer>
#include <QDir>
#include <QUrl>
#include <QFileInfo>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{


    /*ctms_audio_stream test_stream;
    test_stream.volume = 10;
    test_stream.audio_file_path = "c:/Downloads/tyaro.mp3";

    QStringList list1 = str.split(",");*/


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    playersDirector* pd = new playersDirector();
    pd->createPleyers();
    pd->play();


    /*QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile("c:/Downloads/tyaro.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->setVolume(5);
    player->play();*/
/*

    QDir cur_dir = QDir::currentPath();
    QString fileName = cur_dir.filePath("program_player.cfg");
    QFile inputFile(fileName);


    if(QFileInfo::exists(fileName))
    {
        qDebug () << "file exists" << endl;
    }*/
   /* if (inputFile.open(QIODevice::ReadOnly))
    {

       QVector<ctms_audio_stream> stream_vector;

       QTextStream in(&inputFile);
       while (!in.atEnd())  // разбираем в цикле строки конфиг файла и складываем их структурами в вектор
       {
          QString cur_line = in.readLine(); // читаем строки
          if ( cur_line[0] == '#' ) { continue;  }  // пропускаем строки комментов

          QStringList cur_param_arr = cur_line.split(";");
          if (cur_param_arr.size() != 5) { continue;  } // пропускаем не форматные строки
          //file_name;repeatability;first_delay;delay;volume
          ctms_audio_stream cur_stream; // инициализируем структуры для хранения задач
          cur_stream.audio_file_path = cur_param_arr[0];
          cur_stream.repeatability = cur_param_arr[1].toInt();
          cur_stream.first_delay = cur_param_arr[2].toInt();
          cur_stream.delay = cur_param_arr[3].toInt();
          cur_stream.volume = cur_param_arr[4].toInt();
          stream_vector.append(cur_stream);
          int temp = 0;
       }
       int temp = 0;
       inputFile.close();


       // обьявление

       // перебор структур в векторе и запускаем плееры
       foreach( ctms_audio_stream cur_stream, stream_vector ){
           QMediaPlaylist *playlist = new QMediaPlaylist();
           playlist->addMedia(QUrl::fromLocalFile(cur_stream.audio_file_path));
           playlist->setPlaybackMode(QMediaPlaylist::Loop);
           QMediaPlayer *player = new QMediaPlayer();
           player->setPlaylist(playlist);
           player->setVolume(cur_stream.volume);
           player->play();
       }

       temp = 0;

    }*/




/*
    QMediaPlayer *player1 = nullptr;
     player1 = new QMediaPlayer;
     player1->setMedia(QUrl::fromLocalFile("c:/Downloads/5844_Raim_Davletyaro.mp3"));
     player1->setVolume(80);
     player1->play();

     QMediaPlayer *player2 = nullptr;
      player2 = new QMediaPlayer;
      player2->setMedia(QUrl::fromLocalFile("c:/Downloads/vika_dajneko_-_film_ne_o_ljubvi_(zf.fm).mp3"));
      player2->setVolume(20);
      player2->play();
*/
    return a.exec();

}


