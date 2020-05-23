#ifndef CARTE_H
#define CARTE_H

#include <QImage>
#include <QList>
#include <QString>

#include "Model_objetcarte.h"
#include "Model_piege.h"


class Carte
{
private:
    QImage image; //image de la carte

    QList<ObjetCarte> objetsCarte; //objets présents sur la carte
    QList<Piege> piegeCarte; //liste des pieges présents sur la carte


public:
    Carte();
};

#endif // CARTE_H
