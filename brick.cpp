#include "brick.h"


Brick::Brick( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "brick";
}


QRectF Brick::boundingRect() const {
    return QRectF(0,0,50*mLength,50);
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 50*mLength; ++i) {
    painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Brick::getPosX() {
    return this->posX;
}

int Brick::getPosY() {
    return this->posY;
}

QString Brick::getName() {
    return this->name;
}
