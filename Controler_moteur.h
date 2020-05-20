#ifndef MOTEUR_H
#define MOTEUR_H

#include <QGraphicsScene>



class Moteur
{
    //attributs
private:
    QGraphicsScene *scene = NULL;
    QGraphicsView  *view = NULL;

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
