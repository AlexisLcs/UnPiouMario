#ifndef SOL_H
#define SOL_H


#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class Sol : public QGraphicsItem
{
public:
    enum { Type = UserType + solType };
    Sol( int length, QString file, int posX, int posY, int visible,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    int getPosX();
    int getPosY();
    int isVisible();
    QString getName();

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    int visible;
    QString filename;
    QString name;
};

#endif // SOL_H
