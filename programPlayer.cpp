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
  qDebug () << "player first pausa"+ QString::number(progamPlayer::cur_task->first_delay) << endl;
  cur_thread->msleep(progamPlayer::cur_task->first_delay);
  qDebug () << "player play" << endl;
  progamPlayer::playlist = new QMediaPlaylist();
  progamPlayer::playlist->addMedia(QUrl::fromLocalFile(progamPlayer::cur_task->audio_file_path));
  progamPlayer::playlist->setPlaybackMode(QMediaPlaylist::Loop);
  progamPlayer::player = new QMediaPlayer();
  progamPlayer::player->setPlaylist(playlist);
  progamPlayer::player->setVolume(progamPlayer::cur_task->volume);
  progamPlayer::player->play();

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
