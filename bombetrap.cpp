#include "bombetrap.h"

//constructeur
BombeTrap::BombeTrap( int length, QString file, int posX, int posY, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\traps\\" + file);
    this->posX = posX;
    this->posY = posY;
    this->name = "bombetrap";
    this->velocity = 20;
    this->isFalling = false;
}


QRectF BombeTrap::boundingRect() const {
    return QRectF(0,0,50*mLength,111);
}

void BombeTrap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 50*mLength; ++i) {
    painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 111);
    }
    setTransformOriginPoint(boundingRect().center());
}

int BombeTrap::getPosX() {
    return this->posX;
}

int BombeTrap::getPosY() {
    return this->posY;
}

QString BombeTrap::getName() {
    return this->name;
}

//fonction pour la chute
void BombeTrap::FallBomb()
{
    if(isFalling == true)
    {
        if(posY < 800)
        {
            posY += velocity;
            this->setPos(posX, posY);
        }
        else
            this->setVisible(false); //on enleve la bombe de la map quand elle à finit sa chute
    }
}

bool BombeTrap::getIsFalling() const
{
    return isFalling;
}

void BombeTrap::setIsFalling(bool value)
{
    isFalling = value;
}


