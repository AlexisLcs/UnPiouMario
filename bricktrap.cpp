#include "bricktrap.h"

BrickTrap::BrickTrap( int length, QString file, int posX, int posY, QString activation, QString canGoOn, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\hide" + file);
    this->posX = posX;
    this->posY = posY;
    this->activation = activation;
    this->name = "bricktrap";
    this->filename = file;
    this->isActivated = false;
    if(canGoOn == "1"){
        this->canGoOn = false;
    }
    else{
        this->canGoOn = true;
    }
}


QRectF BrickTrap::boundingRect() const {
    return QRectF(0,0,50*mLength,50);
}

void BrickTrap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 50*mLength; ++i) {
    painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
}

void BrickTrap::setPixMap(QString file) {
    this->mPixmap = QPixmap("..\\UnPiouMario\\images\\objects\\" + file);
}

int BrickTrap::getPosX() {
    return this->posX;
}

int BrickTrap::getPosY() {
    return this->posY;
}

QString BrickTrap::getName() {
    return this->name;
}

QString BrickTrap::getFilename() {
    return this->filename;
}

QString BrickTrap::getActivation() {
    return this->activation;
}

bool BrickTrap::getIsActivated() {
    return this->isActivated;
}

void BrickTrap::setIsActivated(bool value) {
    this->isActivated = value;
}

bool BrickTrap::getCanGoOn() {
    return this->canGoOn;
}

void BrickTrap::setCanGoOn(bool value) {
    this->canGoOn = value;
}
