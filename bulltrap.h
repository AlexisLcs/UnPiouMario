#ifndef BULLTRAP_H
#define BULLTRAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class BullTrap : public QGraphicsItem
{
public:
    BullTrap( int length, QString fileL, QString fileR, int posX, int posY, int mDirection, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    int getPosX();
    int getPosY();
    QString getName();

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
};

#endif // BULLTRAP_H
