#include "soundmanager.h"

SoundManager::SoundManager()
{
    // On donne le chemin vers le fichier audio
    this->spikes.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\spikes.wav"));
    // On donne le nombre de seconde à partir duquel il doit boucler (0 ne boucle pas)
    this->spikes.setLoopCount(0);
    // On paramètre le volume audio
    this->spikes.setVolume(.40f);

    this->soltrap.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\soltrap.wav"));
    this->soltrap.setLoopCount(0);
    this->soltrap.setVolume(.40f);

    this->gameover.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\gameover.wav"));
    this->gameover.setLoopCount(0);

    this->win.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\win.wav"));
    this->win.setLoopCount(0);

    this->explosion.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\explosion.wav"));
    this->explosion.setLoopCount(0);
    this->explosion.setVolume(.40f);

    this->bulltrap.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\bulltrap.wav"));
    this->bulltrap.setLoopCount(0);
    this->bulltrap.setVolume(.40f);

    this->jump.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\jump.wav"));
    this->jump.setLoopCount(0);
    this->jump.setVolume(.20f);

    this->jumpbis.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\jumpbis.wav"));
    this->jumpbis.setLoopCount(0);
    this->jumpbis.setVolume(.50f);

    this->jumpter.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\jumpter.wav"));
    this->jumpter.setLoopCount(0);
    this->jumpter.setVolume(.50f);

    this->jumpqat.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\jumpqat.wav"));
    this->jumpqat.setLoopCount(0);
    this->jumpqat.setVolume(.50f);


    this->bip.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\bip.wav"));
    this->bip.setLoopCount(0);
    this->bip.setVolume(2.40f);

    this->fallbomb.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\fallbomb.wav"));
    this->fallbomb.setLoopCount(0);
    this->fallbomb.setVolume(2.40f);

    this->musique.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\musique.wav"));
    // Ici il s'agit de la musique de fond qui boucle 5000 fois
    this->musique.setLoopCount(5000);
    this->musique.setVolume(1.50f);

}
