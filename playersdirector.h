#pragma once

#include <QObject>
#include  "programplayer.h"

class PlayersDirector : public
  QObject   /* класс который запускает враперы плееров */
{
  Q_OBJECT

public:
  PlayersDirector ();
  ~PlayersDirector();
  QVector<AudioTaskConfig> loadPlayersArray ( QString file_name );
  void createPlayers();
  void play();
  void pause();
  void stop();
signals:
  void playAllPlayers();
  void pauseAllPlayers();
  void stopAllPlayers();

};


