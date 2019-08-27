#include <QObject>
#include "programplayer.h"
#include <QDebug>



progamPlayer::progamPlayer (audio_task *task)
{
}


progamPlayer::~progamPlayer()
{

}


void progamPlayer::play(){
    qDebug () << "player play" << endl;
}
void progamPlayer::stop(){
    qDebug () << "player stop" << endl;
}
void progamPlayer::pause(){
  qDebug () << "player pause" << endl;
}
