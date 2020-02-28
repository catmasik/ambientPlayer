#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include "bass.h"


#define STOP_MODE 0
#define PLAY_MODE 1
#define PAUSE_MODE 2


struct AudioTaskConfig
{
  QString audio_file_path;  // путь к аудиофайлу
  int repeatability;  //( 0 - бесконечно, 1- 1 раз и тд.  )
  QString first_delay;    //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
  QString delay;         //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
  int volume;       //  громкость (0-100)
};


void __stdcall syncFunc(HSYNC handle, DWORD channel, DWORD data, void *user);

class AudioThread : public QThread
{
    Q_OBJECT
public:
    explicit AudioThread( AudioTaskConfig t_conf, QObject *parent = 0);
    AudioTaskConfig task_conf ;
    bool playing;
    void run();
    long convertCfgTimeoutToMs(QString cfg_timeout);
    QTimer *timer;
    void sendEndSignalToOwnThread();
    unsigned long chan;

private:
    int timer_was_active;

signals:
    void endOfPlayback();
    void curPos(double Position, double Total);
    void programNextStart();
public slots:
    void play(int mode);
    void pause(int mode);
    void stop(int mode);
    void restartByTimer();
    void changePosition(int position);
    void programStart();
};
#endif // AUDIOTHREAD_H