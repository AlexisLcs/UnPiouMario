#ifndef ENNEMI_H
#define ENNEMI_H

#include "Model_entite.h"

class Ennemi : public Entite
{
private:
    float posMinX; //position min sur la map
    float posMaxX; //position max sur la map

public:

    /*Constructeur*/
    Ennemi();


    /*Getters & setters*/
    float getPosMinX() const;
    void setPosMinX(float value);

    float getPosMaxX() const;
    void setPosMaxX(float value);


    /*Autres méthodes*/
    void WeMustMove(int pas);
};

#endif // ENNEMI_H
