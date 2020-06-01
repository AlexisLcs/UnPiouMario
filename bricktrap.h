#ifndef BRICKTRAP_H
#define BRICKTRAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class BrickTrap : public QGraphicsItem
{
public:
    enum { Type = UserType + brickTrapType };
    BrickTrap( int length, QString file, int posX, int posY, QString activation, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    int getPosX();
    int getPosY();
    QString getName();
    QString getFilename();
    QString getActivation();
    void setPixMap(QString file);


private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    QString filename;
    QString activation;
    QString name;
};

#endif // BRICKTRAP_H
