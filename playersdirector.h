#pragma once

#include <QObject>
#include  "audiothread.h"

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
  void VolumeSliderValueChanged(int value);
  void volumeUp();
  void volumeDown();
  int play_mode;
signals:
  void playAllPlayers(int mode);
  void pauseAllPlayers(int mode);
  void stopAllPlayers(int mode);
  void volumeChanged(int volume);

};



