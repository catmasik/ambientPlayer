#include <QObject>
#include "programplayer.h"
#include <QDebug>
#include <QThread>


SingleSoundPlayer::SingleSoundPlayer ( AudioTaskConfig task )
  : m_task ( task )
  , m_playlist ( new QMediaPlaylist() )
  , m_player ( new QMediaPlayer() )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  //progamPlayer::cur_task = task;
  m_playlist->addMedia ( QUrl::fromLocalFile ( m_task.audio_file_path ) );
  m_playlist->setPlaybackMode ( QMediaPlaylist::Loop );
  m_player->setPlaylist ( m_playlist.get() );
  m_player->setVolume ( m_task.volume );
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}


SingleSoundPlayer::~SingleSoundPlayer()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  m_player->stop();
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}


void SingleSoundPlayer::play()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  //qDebug () << "player first pausa"+ QString::number(progamPlayer::cur_task->first_delay) << endl;
  qDebug () << m_task.audio_file_path;

  QThread::currentThread()->msleep ( m_task.first_delay );
  m_player->play();

  qDebug () << "<- " << __PRETTY_FUNCTION__;
}
void SingleSoundPlayer::stop()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << m_task.audio_file_path;
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}
void SingleSoundPlayer::pause()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << m_task.audio_file_path;
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}
