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

void Mario::setPosX(int value) {
    this->posX = value;
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

void Mario::setCounter(ScreenLabel * label) {
    this->label = label;
}

ScreenLabel * Mario::getCounter() {
    return label;
}

/*Other methods*/
//réinitialise le saut de mario quand il touche le sol ou une plateforme
void Mario::resetJump(){
    velocity[1] = MAXHEIGHT;
    inputMap->remove("Qt::Key_Up");
    inputMap->insert("Qt::Key_Up", false);
}

//Permet à Mario de bouger à gauche
void Mario::moveLeft()
{
    QPixmap pixMario;
    if(isLooking){
        pixMario = QPixmap("..\\UnPiouMario\\images\\mario\\marioskateL.png");
        this->setPixmap(pixMario);
    }
    isLooking = false;
    if(goLeft && this->getPosX() >= 0){
        if(this->getPosX() <= 7400){
            this->setValueScroll(this->scroll->value() - 10);
            if(this->scroll->value() > 0)
                this->getCounter()->setX(this->getCounter()->x() - 10);
        }
        goRight = true;
        setPos(x() - this->velocity[0],y());
        this->posX -= this->velocity[0];
    }
}

//Permet à Mario de bouger à droite
void Mario::moveRight()
{
    QPixmap pixMario;
    if(!isLooking){
        pixMario = QPixmap("..\\UnPiouMario\\images\\mario\\marioskate.png");
        this->setPixmap(pixMario);
    }
    isLooking = true;
    if(goRight && this->getPosX() <= 7880){
        if(this->getPosX() >= 600){
            this->setValueScroll(this->scroll->value() + 10);
            if(this->scroll->value() < 6802)
                this->getCounter()->setX(this->getCounter()->x() + 10);
        }
        goLeft = true;
        setPos(x() + this->velocity[0],y());
        this->posX += this->velocity[0];
    }
}

//Permet à mario de sauter
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
            this->velocity[1] = MAXHEIGHT;
            inputMap->remove("Qt::Key_Up");
            inputMap->insert("Qt::Key_Up", false);

        }
    }
}

//Gère la chute de Mario quand le saut n'attend pas sa valeur final (quand mario saute sur une plateforme plus haute ou plus basse ou qu'il chutte)
void Mario::Fall()
{
    if(!getIsOnGround()) {
        setPos(x(),y()+this->velocity[1]);
        this->posY += this->velocity[1];
        this->velocity[1] = this->velocity[1]+this->gravity[1];
    }
    else {
        setIsFalling(false);
        resetJump();
    }
}

//TODO Lucas spriteUpdater
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

//Permet à Mario d'exécuter les instructions de l'utilisateur
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


//Permet de définir la position du scroller
void Mario::setValueScroll(int value){
    this->scroll->setValue(value);
}






