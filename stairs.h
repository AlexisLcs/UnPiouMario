#ifndef STAIRS_H
#define STAIRS_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class Stairs : public QGraphicsItem
{
public:
    Stairs( int length, QString file, int posX, int posY, int size,QGraphicsItem *parent = 0);
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
    int size;
    QString filename;
    QString name;
};

#endif // STAIRS_H
