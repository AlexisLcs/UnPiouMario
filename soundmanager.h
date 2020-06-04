#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H


#include <QSoundEffect>

class SoundManager
{
public:
    SoundManager();
    QSoundEffect spikes;
    QSoundEffect soltrap;
    QSoundEffect gameover;
    QSoundEffect win;
};

#endif // SOUNDMANAGER_H
