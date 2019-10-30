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
  m_playlist->setPlaybackMode ( QMediaPlaylist::CurrentItemOnce );
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

  QThread::currentThread()->sleep ( m_task.first_delay );
  m_player->play();
  //connect ( m_player, SIGNAL (stateChanged(QMediaPlayer::State state) ), this, SLOT ( restart(QMediaPlayer::State state) ) );

  connect ( *m_player.get(), SIGNAL (stateChanged(QMediaPlayer::State state) ), this, SLOT ( restart(QMediaPlayer::State state) ) );

  qDebug () << "<- " << __PRETTY_FUNCTION__;
}

void SingleSoundPlayer::restart(QMediaPlayer::State state)
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;


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
