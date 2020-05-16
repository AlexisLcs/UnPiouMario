#ifndef CARTE_H
#define CARTE_H

#include <QList>
#include <QString>

#include "objetcarte.h"
#include "piege.h"


class Carte
{
private:
    QString image; //image carte

    QList<ObjetCarte> objetsCarte; //objets présents sur la carte
    QList<Piege> piegeCarte; //liste des pieges présents sur la carte


public:
    Carte();
};

#endif // CARTE_H
