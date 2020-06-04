#include "bulltrap.h"

//constructeur
BullTrap::BullTrap( int length, QString fileL, QString fileR, int posX, int posY, int mDirection, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\traps\\" + fileL);
    this->posX = posX;
    this->posY = posY;
    this->fileL = fileL;
    this->fileR = fileR;
    this->mDirection = mDirection;
    this->name = "bulltrap";
    this->velocity = 20;
}


void BullTrap::nextFrame() {
    if(mDirection == 0){
        mPixmap = QPixmap("..\\test\\images\\traps\\" + fileL);
        mCurrentFrame += 52;
        if (mCurrentFrame >= 156 ) {
            mCurrentFrame = 0;
        }
    }
    else{
        mPixmap = QPixmap("..\\test\\images\\traps\\" + fileR);
        mCurrentFrame += 52;
        if (mCurrentFrame >= 156 ) {
            mCurrentFrame = 0;
        }
    }
}

QRectF BullTrap::boundingRect() const {
    return QRectF(0,0,52*mLength,50);
}

void BullTrap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 52*mLength; ++i) {
    painter->drawPixmap(i*52,0, mPixmap, mCurrentFrame, 0,52, 50);
    }
    setTransformOriginPoint(boundingRect().center());
}

int BullTrap::getPosX() {
    return this->posX;
}

int BullTrap::getPosY() {
    return this->posY;
}

QString BullTrap::getName() {
    return this->name;
}

void BullTrap::moveBullTrap()
{
    //déplacement
    //changement de direction
    if(this->getPosX() < 6260)
        mDirection = 1;
    if(this->getPosX() > 6866)
        mDirection = 0;

    //déplacement en fonction de la direction
    if(mDirection == 1) //if right
    {
        posX += velocity;
    }
    if(mDirection == 0) //if left
    {
        posX -= velocity;
    }


    //partie graphique
    //nextFrame();
    this->setPos(posX, posY);
    //qDebug() << this->getPosX();
}
