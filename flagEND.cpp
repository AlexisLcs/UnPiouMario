#include "flagEND.h"

FlagEND::FlagEND( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "flag";
}


QRectF FlagEND::boundingRect() const {
    return QRectF(0,0,89*mLength,546);
}

void FlagEND::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 89*mLength; ++i) {
    painter->drawPixmap(i*89,0, mPixmap, mCurrentFrame, 0,89, 546);
    }
    setTransformOriginPoint(boundingRect().center());
}

int FlagEND::type() const {
    return Type;
}

int FlagEND::getPosX() {
    return this->posX;
}

int FlagEND::getPosY() {
    return this->posY;
}

QString FlagEND::getName() {
    return this->name;
}
