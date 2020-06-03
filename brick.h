#ifndef BRICKS_H
#define BRICKS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class Brick : public QGraphicsItem
{
public:
    enum { Type = UserType + brickType };
    Brick( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
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

#endif // BRICKS_H
