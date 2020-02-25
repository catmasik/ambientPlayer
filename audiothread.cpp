#include "audiothread.h"
#include <QRegExp>

bool endOfMusic;

void __stdcall syncFunc(HSYNC handle, DWORD channel, DWORD data, void *a_thread)
{
    AudioThread * audio_thread  = (AudioThread *) a_thread;
    audio_thread->sendEndSignalToOwnThread();
}

AudioThread::AudioThread(AudioTaskConfig t_conf, QObject *parent) :
    QThread(parent), task_conf(t_conf)
{
    if (!BASS_Init(-1, 44100, 0, nullptr, nullptr)){
        //qDebug() << "Cannot initialize device";
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(restartByTimer()));
    connect(this, SIGNAL(programNextStart()), this, SLOT(programStart()));
    endOfMusic = true;
}

void AudioThread::play()
{
    BASS_ChannelStop(chan);
    if (!(chan = BASS_StreamCreateFile(false, task_conf.audio_file_path.toLatin1(), 0, 0, 0))
        && !(chan = BASS_MusicLoad(false, task_conf.audio_file_path.toLatin1(), 0, 0, BASS_MUSIC_RAMP, 1))){
            //qDebug() << "Can't play file";
    }else
    {
        endOfMusic = false;
        float cur_volume = float (task_conf.volume)/100;
        BASS_ChannelSetAttribute(chan, BASS_ATTRIB_VOL, cur_volume );
        //BASS_ChannelSetSync(chan, BASS_SYNC_END, 0, &syncFunc, &task_conf);
        BASS_ChannelSetSync(chan, BASS_SYNC_END, 0, &syncFunc, this);

        long first_delay  = this->convertCfgTimeoutToMs(task_conf.first_delay);
        if ( first_delay == 0  ){
            BASS_ChannelPlay(chan, true);
            playing = true;
            ////qDebug() << "playing start"<< task_conf.audio_file_path;
        }else{
            timer->start(first_delay*100);
            //////qDebug() << "playing delayed"<< first_delay;
        }

    }
}

void AudioThread::pause()
{
    //BASS_ChannelPause(chan);
    //timer->stop();
    //playing = false;
    qDebug() << "cach pause signal "<< task_conf.audio_file_path;
}

void AudioThread::resume()
{
    if (!BASS_ChannelPlay(chan, false)){
        //qDebug() << "Error resuming";
    }else
    {
        //t->start(98);
        playing = true;
    }
}

void AudioThread::stop()
{
    BASS_ChannelStop(chan);
    //t->stop();
    playing = false;
}

void AudioThread::restartByTimer()
{
    BASS_ChannelPlay(chan, true);
    playing = true;
    //qDebug() << "playing start"<< task_conf.audio_file_path;
    timer->stop();
}


void AudioThread::sendEndSignalToOwnThread()
{
    emit  programNextStart();
    //qDebug() << "emit programNextStart"<< task_conf.audio_file_path;
}

void AudioThread::programStart()
{
    long delay  = convertCfgTimeoutToMs(task_conf.delay);
    if ( delay == 0  ){
        BASS_ChannelPlay(chan, true);
        //qDebug() << "playing start"<< task_conf.audio_file_path;
    }else{
        timer->start(delay*100);
        //qDebug() << "playing delayed"<< delay;
    }
}


void AudioThread::changePosition(int position)
{
    BASS_ChannelSetPosition(chan, BASS_ChannelSeconds2Bytes(chan, position), BASS_POS_BYTE);
}

void AudioThread::run()
{
    while (1);
}

long AudioThread::convertCfgTimeoutToMs(QString cfg_timeout){
    QRegExp pattern1("\\d*");  // a digit (\d), zero or more times (*)
    if (pattern1.exactMatch(cfg_timeout)){
        return  cfg_timeout.toInt();
    }
    QRegExp pattern2("rnd\\((\\d+)\\-(\\d+)\\)");  // a digit (\d), zero or more times (*)
    if (pattern2.exactMatch(cfg_timeout)){
        int low_lim =  pattern2.cap(1).toInt();
        int high_lim =  pattern2.cap(2).toInt();
        //return  cfg_timeout.toInt();
        int ret_val =  (qrand() % ((high_lim + 1) - low_lim) + low_lim);
        return ret_val;
    }
    return 0;

}
