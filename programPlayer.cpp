#include <QObject>
#include "programplayer.h"
#include <QDebug>
#include <QThread>


progamPlayer::progamPlayer ( audio_task task )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  //progamPlayer::cur_task = task;
  this->cur_task = task;
}


progamPlayer::~progamPlayer()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
}


void progamPlayer::play()
{
  QThread* cur_thread  =  QThread::currentThread();
  //qDebug () << "player first pausa"+ QString::number(progamPlayer::cur_task->first_delay) << endl;
  qDebug () << "player first pausa"+ QString::number(this->cur_task.first_delay) << endl;
  cur_thread->msleep(this->cur_task.first_delay);
  qDebug () << "player play" << endl;
  this->playlist = new QMediaPlaylist();
  this->playlist->addMedia(QUrl::fromLocalFile(this->cur_task.audio_file_path));
  this->playlist->setPlaybackMode(QMediaPlaylist::Loop);
  this->player = new QMediaPlayer();
  this->player->setPlaylist(playlist);
  this->player->setVolume(this->cur_task.volume);
  this->player->play();

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
