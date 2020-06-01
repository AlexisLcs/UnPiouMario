#include "soltrap.h"


SolTrap::SolTrap( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\test\\images\\objects\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "solTrap";
}

QRectF SolTrap::boundingRect() const {
    return QRectF(0,0,64*mLength,64);
}

void SolTrap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 64*mLength; ++i) {
        painter->drawPixmap(i*64,0, mPixmap, mCurrentFrame, 0,64, 64);
    }
    setTransformOriginPoint(boundingRect().center());
}

int SolTrap::getPosX() {
    return this->posX;
}

int SolTrap::getPosY() {
    return this->posY;
}

QString SolTrap::getName() {
    return this->name;
}
