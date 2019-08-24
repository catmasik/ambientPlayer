#ifndef PROGRAMPLAYER_H
#define PROGRAMPLAYER_H
#include <QString>
#include <QObject>

struct audio_task
{
    QString audio_file_path;  // путь к аудиофайлу
    int repeatability;  //( 0 - бесконечно, 1- 1 раз и тд.  )
    int first_delay;    //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
    int delay;         //  ( 100   -  секунды в дес¤тых или  rnd(200-3000)  )
    int volume;       //  громкость (0-100)
};


class progamPlayer : public QObject {
    Q_OBJECT

public:
    progamPlayer(audio_task *task);
    ~progamPlayer();

};

#endif // PROGRAMPLAYER_H
