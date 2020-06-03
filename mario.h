#ifndef MARIO_H
#define MARIO_H
#define MAXHEIGHT 23

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QTimer>
#include <QDebug>

class Mario: public QGraphicsPixmapItem {


private:

    //attributs
    QVector<int> position = QVector<int>(2,0);  // coord X,Y
    QVector<int> velocity = QVector<int>(2,0);  // pas de deplacement
    QVector<int> gravity = QVector<int>(2,0);   // vecteur de gravité
    int posX;
    int posY;
    QPixmap mPixmap;
    bool isJumping = 0;
    bool isFalling = 0;
    bool isOnGround = true;
    bool goRight = true;
    bool goLeft = true;
    bool isLooking; //true vers la droite; false vers la gauche
    int running = 0;
    bool isIdle = 0;

    QMap<QString, bool>* inputMap;

public:
    //constructeur
    Mario(QString file, int posX, int posY);

    //getters & setters
    QVector<int> getPosition() const;
    void setPosition(const QVector<int> &value);
    QVector<int> getVelocity() const;
    void setVelocity(const QVector<int> &value);
    QVector<int> getGravity() const;
    void setGravity(const QVector<int> &value);
    bool getIsJumping();
    void setIsJumping(bool value);
    bool getIsFalling();
    void setIsFalling(bool value);
    bool getGoRight();
    void setGoRight(bool value);
    bool getGoLeft();
    void setGoLeft(bool value);
    bool getIsLooking();
    void setIsLooking(bool value);
    bool getIsOnGround();
    void setIsOnGround(bool value);
    QMap<QString, bool>* getInputMap();
    void setInputMap(QMap<QString, bool>* &value);

    //autres methodes
    void resetJump();
    void moveRight();
    void moveLeft();
    void Jump();
    void spriteUpdater();
    int getPosX();
    int getPosY();
    void moveMario();
};

#endif // MARIO_H
