#include <QObject>
#include <QDir>
#include <QThread>
#include <QVector>
#include <QTextStream>
#include "playersdirector.h"
#include <QDebug>


PlayersDirector::PlayersDirector ()
{
  play_mode = STOP_MODE;
}


PlayersDirector::~PlayersDirector()
{
  //qDebug () << "-> " << __PRETTY_FUNCTION__;

  emit stopAllPlayers(play_mode);
  //qDebug () << "<- " << __PRETTY_FUNCTION__;
}

void PlayersDirector::createPlayers()
{
  //qDebug () << "-> " << __PRETTY_FUNCTION__;
  QVector<AudioTaskConfig> tasks_vector;
  QString file_name = "program_player.cfg";
  tasks_vector = PlayersDirector::loadPlayersArray ( file_name );
  QVector<AudioThread*> audio_threads;
  foreach ( AudioTaskConfig cur_task, tasks_vector )
  {
    //qDebug () << "create player:" << cur_task.audio_file_path;
    auto cur_thread = new AudioThread( cur_task );
    connect ( this, SIGNAL ( playAllPlayers(int) ), cur_thread, SLOT ( play(int) ) );
    connect ( this, SIGNAL ( pauseAllPlayers(int) ), cur_thread, SLOT ( pause(int) ) );
    audio_threads.push_back(cur_thread );
  }
  //qDebug () << "<- " << __PRETTY_FUNCTION__;
}
void PlayersDirector::play()
{
    if ( play_mode == PLAY_MODE ) {
        return;
    }
    if ( play_mode == STOP_MODE ) {
         createPlayers();
         emit  playAllPlayers(play_mode);
    }else{
        if ( play_mode == PAUSE_MODE ) {
            emit  playAllPlayers(play_mode);
        }
    }
    play_mode =  PLAY_MODE;
}
void PlayersDirector::pause()
{
  //qDebug () << "-> " << __PRETTY_FUNCTION__;
  if ( play_mode == PLAY_MODE ) {
      emit  pauseAllPlayers(play_mode);
      play_mode =  PAUSE_MODE;
  }else{
      if ( play_mode == PAUSE_MODE ) {
          emit  playAllPlayers(play_mode);
          play_mode = PLAY_MODE;
      }
  }
}

void PlayersDirector::stop()
{
  emit  stopAllPlayers(  play_mode );
  play_mode = STOP_MODE;
}

QVector<AudioTaskConfig> PlayersDirector::loadPlayersArray ( QString file_name )
{
  //qDebug () << "-> " << __PRETTY_FUNCTION__;
  QDir cur_dir = QDir::currentPath();
  QString fileName = cur_dir.filePath ( file_name );
  //qDebug () << "read_config from:" << fileName;
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
      cur_stream.first_delay = cur_param_arr[2];
      cur_stream.delay = cur_param_arr[3];
      cur_stream.volume = cur_param_arr[4].toInt();
      stream_vector.append ( cur_stream );
      //int temp = 0;
    }

    //int temp = 0;
    inputFile.close();
  }

  //qDebug () << "<- " << __PRETTY_FUNCTION__;
  return  stream_vector;
}
void PlayersDirector::VolumeSliderValueChanged(int value){
    DWORD cur_volume = DWORD (value*100);
    BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, cur_volume);
}

void PlayersDirector::volumeUp(){
    DWORD cur_volume =  BASS_GetConfig( BASS_CONFIG_GVOL_STREAM );
    if (cur_volume+100 < 10000){
        cur_volume+=100;
        BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, cur_volume);
        float slider_pos = float (cur_volume/10000*100);
        emit  volumeChanged(cur_volume);
    }

}
void PlayersDirector::volumeDown(){
    DWORD cur_volume =  BASS_GetConfig( BASS_CONFIG_GVOL_STREAM );
    if (cur_volume > 100){
        cur_volume-=100;
        BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, cur_volume);
        emit  volumeChanged(cur_volume);
    }
}
