#include "sol.h"


Sol::Sol( int length, QString file, int posX, int posY, int visible, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    this->visible = visible;
    if(visible == 1){
        mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\hide" + file);
    }
    else{
        mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
    }
    this->posX = posX;
    this->posY = posY;
    this->name = "sol";
}

QRectF Sol::boundingRect() const {
    return QRectF(0,0,64*mLength,64);
}

void Sol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 64*mLength; ++i) {
    painter->drawPixmap(i*64,0, mPixmap, mCurrentFrame, 0,64, 64);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Sol::getPosX() {
    return this->posX;
}

int Sol::getPosY() {
    return this->posY;
}

int Sol::isVisible() {
    return this->visible;
}

QString Sol::getName() {
    return this->name;
}
