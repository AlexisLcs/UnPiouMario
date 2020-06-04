#ifndef STAIRBLOCK_H
#define STAIRBLOCK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class StairBlock : public QGraphicsItem
{
public:
    enum { Type = UserType + stairBlock };
    StairBlock( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    int getPosX();
    int getPosY();
    QString getName();

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    QString filename;
    QString name;
};

#endif // STAIRBLOCK_H
