#ifndef CASTLE_H
#define CASTLE_H


#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

//classe pour le chateau
class Castle : public QGraphicsItem
{

public:
    //constructeur
    Castle( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

    int getPosX();
    int getPosY();
    QString getName();

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
};

#endif // CASTLE_H
