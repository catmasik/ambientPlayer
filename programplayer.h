#pragma once
#include <QString>
#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>

struct audio_task
{
  QString audio_file_path;  // путь к аудиофайлу
  int repeatability;  //( 0 - бесконечно, 1- 1 раз и тд.  )
  unsigned long first_delay;    //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
  unsigned long delay;         //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
  int volume;       //  громкость (0-100)
};


class progamPlayer : public QObject    /* врапер мультимедиа-плеера */
{
  Q_OBJECT

public:
  progamPlayer ( audio_task* task );
  ~progamPlayer();
  audio_task* cur_task ;
  QMediaPlayer *player;
  QMediaPlaylist *playlist;

public slots:
  void play();
  void stop();
  void pause();

};


