#ifndef SUPERBRICK_H
#define SUPERBRICK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QTimer>

class SuperBrick : public QGraphicsItem
{
public:
    SuperBrick( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
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
    QString filename;
    QString name;
};

#endif // SUPERBRICK_H
