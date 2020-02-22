#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QThread>
#include <QDebug>
#include <QTimer>
#include "bass.h"

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
    void __stdcall syncFunc(HSYNC handle, DWORD channel, DWORD data, void *user);
    AudioTaskConfig task_conf ;
    bool playing;
    void run();
    long convertCfgTimeoutToMs(QString cfg_timeout);

private:
    unsigned long chan;
    QTimer *t;
signals:
    void endOfPlayback();
    void curPos(double Position, double Total);
public slots:
    void play();
    void pause();
    void resume();
    void stop();
    void restartByTimer();
    void changePosition(int position);
};
#endif // AUDIOTHREAD_H
