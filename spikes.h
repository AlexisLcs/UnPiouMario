#ifndef SPIKES_H
#define SPIKES_H


#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "objectype.h"

class Spikes : public QGraphicsItem
{
public:
    enum { Type = UserType + spikesType };
    Spikes( int length, QString file, int posX, int posY, int mDirection,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const {return Type;}
    int getPosX();
    int getPosY();
    QString getFilename();
    QString getName();
    void setPixMap(QString file);
    bool getIsActivated();
    void setIsActivated(bool value);


private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
    int posX;
    int posY;
    QString filename;
    QString name;
    bool isActivated;
};

#endif // SPIKES_H
