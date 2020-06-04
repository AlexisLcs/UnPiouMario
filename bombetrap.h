#ifndef BOMBETRAP_H
#define BOMBETRAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

//classe pour les bombes
class BombeTrap : public QGraphicsItem
{

public:
    enum { Type = UserType + bombTrapType }; //enum pour pouvoir caster l'objet
    BombeTrap( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0); //constructeur

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    void FallBomb();

    //getters & setters
    int getPosX();
    int getPosY();
    QString getName();  
    bool getIsFalling() const;
    void setIsFalling(bool value);

private:
    //attributs
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    QString filename;
    QString name;
    int velocity;
    bool isFalling;
};

#endif // BOMBETRAP_H
