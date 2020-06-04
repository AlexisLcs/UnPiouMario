#include "soundmanager.h"

SoundManager::SoundManager()
{
    this->spikes.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\spikes.wav"));
    this->spikes.setLoopCount(0);
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
    this->jump.setVolume(.40f);

    this->bip.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\bip.wav"));
    this->bip.setLoopCount(0);
    this->bip.setVolume(2.40f);

    this->fallbomb.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\fallbomb.wav"));
    this->fallbomb.setLoopCount(0);
    this->fallbomb.setVolume(2.40f);

    this->musique.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\musique.wav"));
    this->musique.setLoopCount(5000);
    this->musique.setVolume(1.50f);

}
