#include "mario.h"

/*Constructor*/

Mario::Mario(QString file, int posX, int posY)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\mario\\" + file);
    this->posX = posX;
    this->posY = posY;
    velocity[0] = 10;
    velocity[1] = MAXHEIGHT;
    gravity[1] = 1;
}


/*Getters & setters*/

QVector<int> Mario::getPosition() const
{
    return position;
}

int Mario::getPosX() {
    return this->posX;
}

int Mario::getPosY() {
    return this->posY;
}
void Mario::setPosition(const QVector<int> &value)
{
    position = value;
}
QVector<int> Mario::getVelocity() const
{
    return velocity;
}
void Mario::setVelocity(const QVector<int> &value)
{
    velocity = value;
}
QVector<int> Mario::getGravity() const
{
    return gravity;
}
void Mario::setGravity(const QVector<int> &value)
{
    gravity = value;
}
bool Mario::getIsJumping() const
{
    return isJumping;
}
void Mario::setIsJumping(bool value)
{
    isJumping = value;
}
bool Mario::getIsFalling() const
{
    return isFalling;
}
void Mario::setIsFalling(bool value)
{
    isFalling = value;
}
QMap<int, bool> Mario::getInputMap() const
{
    return inputMap;
}

void Mario::setInputMap(const QMap<int, bool> &value)
{
    inputMap = value;
}



/*Other methods*/

void Mario::moveLeft()
{
    if(isJumping)
        Jump();

    setPos(x() - this->velocity[0],y());
    this->posX -= this->velocity[0];
}

void Mario::moveRight()
{
    if(isJumping)
        Jump();

    setPos(x() + this->velocity[0],y());
    this->posX += this->velocity[0];
}

//ATTENTION : quand on appelle cette méthode on suppose que isJumping == true
void Mario::Jump()
{
        if(!isJumping) {
            isJumping = true;
        }


    //si on est en état saut
    if(isJumping)
    {
        qDebug() << this->velocity[1];

        //monter
        if(this->velocity[1] > 0 && !isFalling)
        {
            setPos(x(),y()-this->velocity[1]); //changement coord
            this->posY -= this->velocity[1];
            this->velocity[1] = this->velocity[1]-this->gravity[1]; //
        }
        //passage en mode "chute"
        else if(this->velocity[1] <= MAXHEIGHT){
            if(this->velocity[1] == 0) {
                isFalling = true;
            }
            setPos(x(),y()+this->velocity[1]);
            this->posY += this->velocity[1];
            this->velocity[1] = this->velocity[1]+this->gravity[1];
        }
        else if(this->velocity[1] == MAXHEIGHT+1 && isFalling) {
            isJumping = false;
            isFalling = false;
            this->velocity[1] = MAXHEIGHT;
        }
    }
}

void Mario::spriteUpdater() {
    if(isJumping){
        this->setPixmap(QPixmap("..\\images\\mario\\mario_jump.png"));
    }
    else if(!isIdle){
        if(running >= 0 && running < 3){
            this->setPixmap(QPixmap("..\\images\\mario\\mario_course1.png"));
            running++;
        }
        else if(running >= 3 && running < 6){
            this->setPixmap(QPixmap("..\\images\\mario\\mario_course2.png"));
            running++;
        }
        else if(running >= 6 && running < 9){
            this->setPixmap(QPixmap("..\\images\\mario\\mario_course3.png"));
            running = 1;
        }
    }
    else {
        this->setPixmap(QPixmap("..\\images\\mario\\mario_stop.png"));
    }
}

void Mario::timerOutEvent()
{
    if(inputMap[Qt::Key_Right])
    {
        moveRight();
    }

    if(inputMap[Qt::Key_Left])
    {
        moveLeft();
    }

    if(inputMap[Qt::Key_Up])
    {
        Jump();
    }
}






