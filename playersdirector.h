#ifndef PLAYERSDIRECTOR_H
#define PLAYERSDIRECTOR_H

#include <QObject>
#include  "programplayer.h"

class playersDirector : public QObject { /* класс который запускает враперы плееров */
    Q_OBJECT

public:
    playersDirector();
    ~playersDirector();
    QVector<audio_task> loadPlayersArray(QString file_name);
    void createPleyers();
    void play();
    void pause();
    void stop();
signals:
   void playAllPlayers();
   void pausePlayers();
   void stopAllPlayers();

};


#endif // PLAYERSDIRECTOR_H
