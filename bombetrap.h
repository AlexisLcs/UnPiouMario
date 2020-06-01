#ifndef BOMBETRAP_H
#define BOMBETRAP_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class BombeTrap : public QGraphicsItem
{
public:
    BombeTrap( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
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

#endif // BOMBETRAP_H
