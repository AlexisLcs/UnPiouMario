#include "Model_entite.h"

//contructeur par défaut
Entite::Entite()
{

}

/*Getters */

int Entite::getVoiciLaVie() const
{
    return voiciLaVie;
}

void Entite::setVoiciLaVie(int value)
{
    voiciLaVie = value;
}

float Entite::getScoutEnY() const
{
    return scoutEnY;
}

void Entite::setScoutEnY(float value)
{
    scoutEnY = value;
}

float Entite::getOuTuEsX() const
{
    return ouTuEsX;
}

void Entite::setOuTuEsX(float value)
{
    ouTuEsX = value;
}

int Entite::getCMaDirection() const
{
    return cMaDirection;
}

void Entite::setCMaDirection(int value)
{
    cMaDirection = value;
}


