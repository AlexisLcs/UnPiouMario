#include "soundmanager.h"

SoundManager::SoundManager()
{
    this->spikes.setSource(QUrl::fromLocalFile("D:\\Félix\\Documents\\Polytech 4A\\S8\\QT\\Projet_UnfairMario\\UnPiouMario\\sounds\\spikes.wav"));
    this->spikes.setLoopCount(0);
    this->spikes.setVolume(.25f);
}
