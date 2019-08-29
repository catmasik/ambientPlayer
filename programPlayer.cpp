#include <QObject>
#include "programplayer.h"
#include <QDebug>
#include <QThread>


progamPlayer::progamPlayer ( audio_task* task )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  progamPlayer::cur_task = task;
}


progamPlayer::~progamPlayer()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
}


void progamPlayer::play()
{
    QThread* cur_thread  =  QThread::currentThread();
    cur_thread->msleep(5000);
    qDebug () << "player play" << endl;
}
void progamPlayer::stop()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << "player stop" << endl;
}
void progamPlayer::pause()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << "player pause" << endl;
}
