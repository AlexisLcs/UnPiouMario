#include "mario.h"

/*Constructor*/

Mario::Mario(QScrollBar* s, QString file, int posX, int posY)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap("..\\UnPiouMario\\images\\mario\\" + file);
    this->posX = posX;
    this->posY = posY;
    velocity[0] = 10;
    velocity[1] = MAXHEIGHT;
    gravity[1] = 1;
    this->scroll = s;
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
bool Mario::getIsJumping()
{
    return isJumping;
}
void Mario::setIsJumping(bool value)
{
    isJumping = value;
}
bool Mario::getIsFalling()
{
    return isFalling;
}
void Mario::setIsFalling(bool value)
{
    isFalling = value;
}
bool Mario::getGoRight()
{
    return goRight;
}
void Mario::setGoRight(bool value)
{
    goRight = value;
}
bool Mario::getGoLeft()
{
    return goLeft;
}
void Mario::setGoLeft(bool value)
{
    goLeft = value;
}
bool Mario::getIsLooking()
{
    return isLooking;
}
void Mario::setIsLooking(bool value)
{
    isLooking = value;
}

bool Mario::getIsOnGround()
{
    return isOnGround;
}
void Mario::setIsOnGround(bool value)
{
    isOnGround = value;
}
QMap<QString, bool>* Mario::getInputMap()
{
    return inputMap;
}

void Mario::setInputMap(QMap<QString, bool>* &value)
{
    inputMap = value;
}



/*Other methods*/
void Mario::resetJump(){
    velocity[1] = MAXHEIGHT;
    inputMap->remove("Qt::Key_Up");
    inputMap->insert("Qt::Key_Up", false);
}

void Mario::moveLeft()
{
    isLooking = false;
    if(goLeft && this->getPosX() >= 0){
        if(this->getPosX() <= 7400){
            this->setValueScroll(this->scroll->value() - 10);
        }
        goRight = true;
        setPos(x() - this->velocity[0],y());
        this->posX -= this->velocity[0];
    }
}

void Mario::moveRight()
{
    isLooking = true;
    if(goRight && this->getPosX() <= 7880){
        if(this->getPosX() >= 600){
            this->setValueScroll(this->scroll->value() + 10);
        }
        goLeft = true;
        setPos(x() + this->velocity[0],y());
        this->posX += this->velocity[0];
    }
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
        //monter
        if(this->velocity[1] > 0 && !isFalling)
        {
            setPos(x(),y()-this->velocity[1]); //changement coord
            this->posY -= this->velocity[1];
            this->velocity[1] = this->velocity[1]-this->gravity[1];
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
            inputMap->remove("Qt::Key_Up");
            inputMap->insert("Qt::Key_Up", false);
        }
    }
}

void Mario::Fall()
{
    if(!getIsOnGround()){
        setPos(x(),y()+this->velocity[1]);
        this->posY += this->velocity[1];
        this->velocity[1] = this->velocity[1]+this->gravity[1];
    }
    else {
        setIsFalling(false);
        resetJump();
    }
}

void Mario::spriteUpdater() {
    if(isJumping){
        this->setPixmap(QPixmap("..\\UnPiouMario\\images\\mario\\mario_jump.png"));
    }
    else if(!isIdle){
        if(running >= 0 && running < 3){
            this->setPixmap(QPixmap("..\\UnPiouMario\\images\\mario\\mario_course1.png"));
            running++;
        }
        else if(running >= 3 && running < 6){
            this->setPixmap(QPixmap("..\\UnPiouMario\\images\\mario\\mario_course2.png"));
            running++;
        }
        else if(running >= 6 && running < 9){
            this->setPixmap(QPixmap("..\\UnPiouMario\\images\\mario\\mario_course3.png"));
            running = 1;
        }
    }
    else {
        this->setPixmap(QPixmap("..\\UnPiouMario\\images\\mario\\mario_stop.png"));
    }
}

void Mario::moveMario()
{

    if(inputMap->value("Qt::Key_Right"))
    {
        moveRight();
    }

    if(inputMap->value("Qt::Key_Left"))
    {
        moveLeft();
    }

    if(inputMap->value("Qt::Key_Up"))
    {
        Jump();
    }
    else //if(getIsFalling())
    {
        Fall();
    }
}



void Mario::setValueScroll(int value){
    this->scroll->setValue(value);
}






