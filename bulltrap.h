#ifndef BULLTRAP_H
#define BULLTRAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class BullTrap : public QGraphicsItem
{
public:
    enum { Type = UserType + bullTrapType };
    BullTrap( int length, QString fileL, QString fileR, int posX, int posY, int mDirection, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    int getPosX();
    int getPosY();
    QString getName();
    void moveBullTrap();

public slots:
    void nextFrame();

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    QString fileL;
    QString fileR;
    QString name;
    int velocity;
};

#endif // BULLTRAP_H
