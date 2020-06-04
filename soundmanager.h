#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H


#include <QSoundEffect>
#include <QMediaPlayer>

class SoundManager
{
public:
    SoundManager();
    QSoundEffect spikes;
    QSoundEffect soltrap;
    QSoundEffect gameover;
    QSoundEffect win;
    QSoundEffect explosion;
    QSoundEffect bulltrap;
    QSoundEffect jump;
    QSoundEffect musique;
    QSoundEffect bip;
    QSoundEffect fallbomb;
};

#endif // SOUNDMANAGER_H
