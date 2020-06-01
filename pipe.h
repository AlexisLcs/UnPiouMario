#ifndef PIPELIT_H
#define PIPELIT_H


#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class Pipe : public QGraphicsItem
{
public:
    Pipe( int length, QString file, int posX, int posY, int sizePipe ,QGraphicsItem *parent = 0);
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
    int sizePipe;
    QString filename;
    QString name;
};

#endif // PIPELIT_H
