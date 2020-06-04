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
    void FallBomb();
    bool getIsFalling() const;
    void setIsFalling(bool value);

private:
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
