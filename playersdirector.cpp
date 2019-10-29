#include <QObject>
#include <QDir>
#include <QThread>
#include <QVector>
#include <QTextStream>
#include "playersdirector.h"
#include "programplayer.h"
#include <QDebug>


PlayersDirector::PlayersDirector ()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}


PlayersDirector::~PlayersDirector()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;

  emit stopAllPlayers();
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}

void PlayersDirector::createPlayers()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  QVector<AudioTaskConfig> tasks_vector;
  QString file_name = "program_player.cfg";
  tasks_vector = PlayersDirector::loadPlayersArray ( file_name );

  foreach ( AudioTaskConfig cur_task, tasks_vector )
  {
    qDebug () << "create player:" << cur_task.audio_file_path;
    auto* player = new SingleSoundPlayer ( cur_task );
    auto* thread = new QThread ;
    player->moveToThread ( thread );
    connect ( this, SIGNAL ( playAllPlayers() ), player, SLOT ( play() ) );
    connect ( this, SIGNAL ( pauseAllPlayers() ), player, SLOT ( pause() ) );
    connect ( this, SIGNAL ( stopAllPlayers() ), player, SLOT ( stop() ) );

        thread->start();
        //if(loop_cnt==2){continue;}

  }
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}
void PlayersDirector::play()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  emit  playAllPlayers();
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}
void PlayersDirector::pause()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  emit  pauseAllPlayers();
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}

void PlayersDirector::stop()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  emit  stopAllPlayers();
  qDebug () << "<- " << __PRETTY_FUNCTION__;
}

QVector<AudioTaskConfig> PlayersDirector::loadPlayersArray ( QString file_name )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  QDir cur_dir = QDir::currentPath();
  QString fileName = cur_dir.filePath ( file_name );
  QFile inputFile ( fileName );

  QVector<AudioTaskConfig> stream_vector;

  if ( inputFile.open ( QIODevice::ReadOnly ) )
  {
    QTextStream in ( &inputFile );

    while ( !in.atEnd() ) // разбираем в цикле строки конфиг файла и складываем их структурами в вектор
    {
      QString cur_line = in.readLine(); // читаем строки

      if ( cur_line[0] == '#' )
      {
        continue;   // пропускаем строки комментов
      }

      QStringList cur_param_arr = cur_line.split ( ";" );

      if ( cur_param_arr.size() != 5 )
      {
        continue;   // пропускаем не форматные строки
      }

      //file_name;repeatability;first_delay;delay;volume
      AudioTaskConfig cur_stream; // инициализируем структуры для хранения задач
      cur_stream.audio_file_path = cur_param_arr[0];
      cur_stream.repeatability = cur_param_arr[1].toInt();
      cur_stream.first_delay = cur_param_arr[2].toULong();
      cur_stream.delay = cur_param_arr[3].toULong();
      cur_stream.volume = cur_param_arr[4].toInt();
      stream_vector.append ( cur_stream );
      //int temp = 0;
    }

    //int temp = 0;
    inputFile.close();
  }

  qDebug () << "<- " << __PRETTY_FUNCTION__;
  return  stream_vector;
}
