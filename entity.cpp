#include "entity.h"

Mario *Entity::getMario() const
{
    return mario;
}

void Entity::setMario(Mario *value)
{
    mario = value;
}

QTimer *Entity::getInputTimer() const
{
    return inputTimer;
}

void Entity::setInputTimer(QTimer *value)
{
    inputTimer = value;
}

Entity::Entity(Mario * mario)
{
    this->mario = mario;
/*
    //timer pour les input
    inputTimer = new QTimer(this);

    //connexion au timer pour les input uniquement
    connect(inputTimer, SIGNAL(timeout()), this,
            SLOT(marioInput()));

    inputTimer->start(16);*/
}
/*
void Entity::marioInput()
{
    mario->timerOutEvent();
}*/

