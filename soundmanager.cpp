#include "soundmanager.h"

SoundManager::SoundManager()
{
    this->spikes.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\spikes.wav"));
    this->spikes.setLoopCount(0);
    this->spikes.setVolume(.25f);

    this->soltrap.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\soltrap.wav"));
    this->soltrap.setLoopCount(0);
    this->soltrap.setVolume(.25f);

    this->gameover.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\gameover.wav"));
    this->soltrap.setLoopCount(0);
    this->soltrap.setVolume(.25f);

    this->win.setSource(QUrl::fromLocalFile("..\\UnPiouMario\\sounds\\win.wav"));
    this->soltrap.setLoopCount(0);
    this->soltrap.setVolume(.25f);
}
