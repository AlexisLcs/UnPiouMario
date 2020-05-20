#ifndef JOUEUR_H
#define JOUEUR_H
#include "Model_entite.h"

class Joueur : public Entite
{

public:

    /*Constructeur*/
    Joueur();

    /*Autres méthodes*/
    void JeanneAuSecours(); //déplacement a droite
    void decaleGwada(); //deplacement à gauche
    void jumpAround(); //sauter

};

#endif // JOUEUR_H
