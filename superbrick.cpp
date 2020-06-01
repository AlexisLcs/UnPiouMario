#include "superbrick.h"


SuperBrick::SuperBrick( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "superbrick";
}

void SuperBrick::nextFrame() {
    mCurrentFrame += 48;
    if (mCurrentFrame >= 800 ) {
        mCurrentFrame = 0;
    }
}


QRectF SuperBrick::boundingRect() const {
    return QRectF(0,0,50*mLength,50);
}

void SuperBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 50*mLength; ++i) {
    painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
}

int SuperBrick::type() const {
    return Type;
}

int SuperBrick::getPosX() {
    return this->posX;
}

int SuperBrick::getPosY() {
    return this->posY;
}

QString SuperBrick::getName() {
    return this->name;
}
