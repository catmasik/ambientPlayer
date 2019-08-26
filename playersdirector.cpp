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

}


playersDirector::~playersDirector()
{

}


void playersDirector::runPleyers(){

    QVector<audio_task> tasks_vector;
    QString file_name = "program_player.cfg";
    tasks_vector = loadPlayersArray(file_name);

    foreach( audio_task cur_task, tasks_vector ){
        progamPlayer* cur_player = new progamPlayer(&cur_task);
        QThread* thread = new QThread;
        cur_player->moveToThread(thread);
    }


}



QVector<audio_task> playersDirector::loadPlayersArray(QString file_name)
{
    QDir cur_dir = QDir::currentPath();
    QString fileName = cur_dir.filePath(file_name);
    QFile inputFile(fileName);

    if(QFileInfo::exists(fileName))
    {
        qDebug () << "file exists" << endl;
    }
    QVector<audio_task> stream_vector;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())  // разбираем в цикле строки конфиг файла и складываем их структурами в вектор
       {
          QString cur_line = in.readLine(); // читаем строки
          if ( cur_line[0] == '#' ) { continue;  }  // пропускаем строки комментов

          QStringList cur_param_arr = cur_line.split(";");
          if (cur_param_arr.size() != 5) { continue;  } // пропускаем не форматные строки
          //file_name;repeatability;first_delay;delay;volume
          audio_task cur_stream; // инициализируем структуры для хранения задач
          cur_stream.audio_file_path = cur_param_arr[0];
          cur_stream.repeatability = cur_param_arr[1].toInt();
          cur_stream.first_delay = cur_param_arr[2].toInt();
          cur_stream.delay = cur_param_arr[3].toInt();
          cur_stream.volume = cur_param_arr[4].toInt();
          stream_vector.append(cur_stream);
          //int temp = 0;
       }
       //int temp = 0;
       inputFile.close();
    }
    return  stream_vector;
}
