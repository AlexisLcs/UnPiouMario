#include "stairs.h"


Stairs::Stairs( int length, QString file, int posX, int posY, int size, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\test\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->size = size;
    this->name = "stairs";
}


QRectF Stairs::boundingRect() const {
    if(this->size == 1){
        return QRectF(0,0,256*mLength,256);
    }
    else if(this->size == 2){
        return QRectF(0,0,320*mLength,256);
    }
    return QRectF(0,0,384*mLength,383);
}

void Stairs::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    if(this->size == 1){
        for(int i = 0; i < 256*mLength; ++i) {
            painter->drawPixmap(i*256,0, mPixmap, mCurrentFrame, 0,256, 256);
        }
    }
    else if(this->size == 2){
        for(int i = 0; i < 320*mLength; ++i) {
            painter->drawPixmap(i*320,0, mPixmap, mCurrentFrame, 0,320, 256);
        }
    }
    else{
        for(int i = 0; i < 384*mLength; ++i) {
            painter->drawPixmap(i*384,0, mPixmap, mCurrentFrame, 0,384, 383);
        }
    }
    setTransformOriginPoint(boundingRect().center());
}

int Stairs::type() const {
    return Type;
}

int Stairs::getPosX() {
    return this->posX;
}

int Stairs::getPosY() {
    return this->posY;
}


QString Stairs::getName() {
    return this->name;
}
