#include "soundmanager.h"

SoundManager::SoundManager()
{
    this->spikes.setSource(QUrl::fromLocalFile("../test/sounds/spikes.wav"));
    this->spikes.setLoopCount(0);
    this->spikes.setVolume(.25f);
}
