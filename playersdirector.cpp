#include <QObject>
#include <QThread>
#include "playersdirector.h"
#include "programplayer.h"



playersDirector::playersDirector ()
{
        audio_task task; // инициализируем структуры для хранения задач
        progamPlayer* player = new progamPlayer( &task);
        QThread* thread = new QThread;
        player->moveToThread(thread);

}


playersDirector::~playersDirector()
{

}
