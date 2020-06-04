#include "StairBlock.h"

StairBlock::StairBlock( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "stairblock";
}


QRectF StairBlock::boundingRect() const {
    return QRectF(0,0,64*mLength,64);
}

void StairBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 64*mLength; ++i) {
    painter->drawPixmap(i*64,0, mPixmap, mCurrentFrame, 0,64, 64);
    }
    setTransformOriginPoint(boundingRect().center());
}

int StairBlock::getPosX() {
    return this->posX;
}

int StairBlock::getPosY() {
    return this->posY;
}

QString StairBlock::getName() {
    return this->name;
}
