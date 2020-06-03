#ifndef ENTITY_H
#define ENTITY_H

#include "mario.h"

#include <QObject>

class Entity : public QObject
{
    Q_OBJECT

private:
    //Attributs


public:
    //constructor
    Entity(Mario *mario);
    Mario *mario;
    QTimer *inputTimer;
    //getters & setters

    Mario *getMario() const;
    void setMario(Mario *value);
    QTimer *getInputTimer() const;
    void setInputTimer(QTimer *value);
};

#endif // ENTITY_H
