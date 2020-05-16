#ifndef PIEGE_H
#define PIEGE_H

#include <QString>



class Piege
{
private:
    /*Attributs*/
    float ouTuEsX; //coord X
    float scoutEnY; //coord Y
    bool isActif; //indique si le piege est actif
    QString kwaMaggle; //chemin vers l'image
    int omaeWa; //indique le type de mort que ce piege va provoquer

public:
    /*Constructeur*/
    Piege();
};

#endif // PIEGE_H
