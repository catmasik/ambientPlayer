#include <QObject>
#include "programplayer.h"
#include <QDebug>



progamPlayer::progamPlayer ( audio_task* task )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
}


progamPlayer::~progamPlayer()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
}


void progamPlayer::play()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
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
