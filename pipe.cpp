#include "pipe.h"

Pipe::Pipe( int length, QString file, int posX, int posY, int sizePipe, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->sizePipe = sizePipe;
    this->name = "pipe";
}


QRectF Pipe::boundingRect() const {
    if(this->sizePipe == 1){
        return QRectF(0,0,75*mLength,75);
    }
    else if(this->sizePipe == 2){
        return QRectF(0,0,75*mLength,113);
    }
    return QRectF(0,0,75*mLength,150);
}

void Pipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

    if(this->sizePipe == 1){
        for(int i = 0; i < 75*mLength; ++i) {
            painter->drawPixmap(i*75,0, mPixmap, mCurrentFrame, 0,75, 75);
        }
    }
    else if(this->sizePipe == 2){
        for(int i = 0; i < 75*mLength; ++i) {
            painter->drawPixmap(i*75,0, mPixmap, mCurrentFrame, 0,75, 113);
        }
    }
    else{
        for(int i = 0; i < 75*mLength; ++i) {
            painter->drawPixmap(i*75,0, mPixmap, mCurrentFrame, 0,75, 150);
        }
    }
    setTransformOriginPoint(boundingRect().center());
}

int Pipe::getPosX() {
    return this->posX;
}

int Pipe::getPosY() {
    return this->posY;
}

QString Pipe::getName() {
    return this->name;
}
