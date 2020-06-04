#ifndef FLAG_H
#define FLAG_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

//classe pour le drapeau de fin
class FlagEND : public QGraphicsItem
{
public:
    //constructeur
    FlagEND( int length, QString file, int posX, int posY,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    //getters & setters
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

#endif // FLAG_H
