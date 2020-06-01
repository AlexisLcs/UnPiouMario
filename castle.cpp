#include "castle.h"


Castle::Castle( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\test\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "castle";
}


QRectF Castle::boundingRect() const {
    return QRectF(0,0,200*mLength,201);
}

void Castle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 365*mLength; ++i) {
    painter->drawPixmap(i*200,0, mPixmap, mCurrentFrame, 0,200, 201);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Castle::type() const {
    return Type;
}

int Castle::getPosX() {
    return this->posX;
}

int Castle::getPosY() {
    return this->posY;
}

QString Castle::getName() {
    return this->name;
}
