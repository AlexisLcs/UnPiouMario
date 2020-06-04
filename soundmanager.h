#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H


#include <QSoundEffect>

class SoundManager
{
public:
    SoundManager();
    //Déclaration de tous les objets correspondant à un bruit
    QSoundEffect spikes;
    QSoundEffect soltrap;
    QSoundEffect gameover;
    QSoundEffect gameovermario;
    QSoundEffect win;
    QSoundEffect explosion;
    QSoundEffect bulltrap;
    QSoundEffect musique;
    QSoundEffect bip;
    QSoundEffect fallbomb;
    QSoundEffect jump;
    QSoundEffect jumpbis;
    QSoundEffect jumpter;
    QSoundEffect jumpqat;
};

#endif // SOUNDMANAGER_H
