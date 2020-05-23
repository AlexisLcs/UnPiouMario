#ifndef MOTEUR_H
#define MOTEUR_H

#include "Model_carte.h"
#include <QGraphicsScene>



class Moteur
{
    //attributs
private:
    QGraphicsScene *scene = NULL;
    QGraphicsView  *view = NULL;
    Carte *carte = NULL;

public:

    /*constructeur*/
    Moteur();

    /*methodes*/
    void loadingGame();


    inline QGraphicsScene* getScene() {
        return scene;
    }


    inline QGraphicsView *getView() {
        return view;
    }
};

#endif // MOTEUR_H
