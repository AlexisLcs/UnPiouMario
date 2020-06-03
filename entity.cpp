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
}

