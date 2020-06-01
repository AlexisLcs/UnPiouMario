#include "spikes.h"


Spikes::Spikes( int length, QString file, int posX, int posY, int mDirection, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\test\\images\\traps\\hide" + file);
    this->posX = posX;
    this->posY = posY;
    this->mDirection = mDirection;
    this->name = "spikes";
    this->filename = file;
}

QRectF Spikes::boundingRect() const {
    return this->mDirection==0?QRectF(0,0,50*mLength,37):QRectF(0,0,37*mLength,50);
}

void Spikes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    if(this->mDirection == 0){
        for(int i = 0; i < 50*mLength; ++i) {
            painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 37);
        }
    }
    else{
        for(int i = 0; i < 37*mLength; ++i) {
            painter->drawPixmap(i*37,0, mPixmap, mCurrentFrame, 0,37, 50);
        }
    }
    setTransformOriginPoint(boundingRect().center());
}

int Spikes::getPosX() {
    return this->posX;
}

int Spikes::getPosY() {
    return this->posY;
}

void Spikes::setPixMap(QString file) {
    this->mPixmap = QPixmap("..\\test\\images\\traps\\" + file);
}

QString Spikes::getName() {
    return this->name;
}

QString Spikes::getFilename() {
    return this->filename;
}
