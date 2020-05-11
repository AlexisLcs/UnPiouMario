#ifndef ENTITE_H
#define ENTITE_H

#include <QString>



class Entite
{
private:

    /*attributs*/
    float ouTuEsX; //coord X
    float scoutEnY; //coord Y
    int voiciLaVie; //points de vie
    int cMaDirection; //indique l'orientation du personnage
    QString kwaMaggle; //indique le chemin vers l'asset pour l'entite


public:

    /*Constructeurs*/
    Entite();


    /*Getters & setters*/
    float getOuTuEsX() const;
    void setOuTuEsX(float value);

    float getScoutEnY() const;
    void setScoutEnY(float value);

    int getVoiciLaVie() const;
    void setVoiciLaVie(int value);

    int getCMaDirection() const;
    void setCMaDirection(int value);


    /*Autres méthodes*/
    bool PasTouchay(); //hitbox

    void FireInTheHole(); //tirer


};

#endif // ENTITE_H
