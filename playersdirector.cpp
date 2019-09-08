#include <QObject>
#include <QDir>
#include <QThread>
#include <QVector>
#include <QTextStream>
#include "playersdirector.h"
#include "programplayer.h"
#include <QDebug>


playersDirector::playersDirector ()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;

}


playersDirector::~playersDirector()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;

}

void playersDirector::createPleyers()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << "director create players" << endl;
  QVector<audio_task> tasks_vector;
  QString file_name = "program_player.cfg";
  tasks_vector = playersDirector::loadPlayersArray ( file_name );
  int loop_cnt = 0;
  foreach( audio_task cur_task, tasks_vector ){
         qDebug () << "create player" << endl;
        progamPlayer* cur_player = new progamPlayer(cur_task);
        connect(this, SIGNAL(playAllPlayers()), cur_player, SLOT(play()));
        connect(this, SIGNAL(pauseAllPlayers()), cur_player, SLOT(pause()));
        connect(this, SIGNAL(stopAllPlayers()), cur_player, SLOT(stop()));
        QThread* thread = new QThread;
        cur_player->moveToThread(thread);
        thread->start();
        loop_cnt++;
        //if(loop_cnt==2){continue;}

  }
}
void playersDirector::play()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  qDebug () << "director switch play all players" << endl;
  emit  playAllPlayers();
}
void playersDirector::pause()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  emit  pauseAllPlayers();
}

void playersDirector::stop()
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  emit  stopAllPlayers();

}

QVector<audio_task> playersDirector::loadPlayersArray ( QString file_name )
{
  qDebug () << "-> " << __PRETTY_FUNCTION__;
  QDir cur_dir = QDir::currentPath();
  QString fileName = cur_dir.filePath ( file_name );
  QFile inputFile ( fileName );

  QVector<audio_task> stream_vector;

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
      audio_task cur_stream; // инициализируем структуры для хранения задач
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

  return  stream_vector;
}
