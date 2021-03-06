#ifndef ENTITY_H
#define ENTITY_H

#include "mario.h"

#include <QObject>

//classe pour contenir le mario et implémenter un timer (celui ci est encore présent mais il n'est plus utilisé, nous l'avons laissé si besoin)
class Entity : public QObject
{
    Q_OBJECT
public:
    //constructor
    Entity(Mario *mario);

    //attributs (oui les attributs en public c'est pas propre mais ca marche)
    //nous avons quand même fait l'effort d'utiliser les getters & setters
    Mario *mario;
    QTimer *inputTimer;

    //getters & setters
    Mario *getMario() const;
    void setMario(Mario *value);
    QTimer *getInputTimer() const;
    void setInputTimer(QTimer *value);
};

#endif // ENTITY_H
