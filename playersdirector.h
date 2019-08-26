#ifndef PLAYERSDIRECTOR_H
#define PLAYERSDIRECTOR_H

#include <QObject>
#include  "programplayer.h"

class playersDirector : public QObject {
    Q_OBJECT

public:
    playersDirector();
    ~playersDirector();
    QVector<audio_task>* loadPlayersArray(QString file_name);
    void runPleyers();


};


#endif // PLAYERSDIRECTOR_H
