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
    bool getIsJumping() const;
    void setIsJumping(bool value);
    bool getIsFalling() const;
    void setIsFalling(bool value);

    QMap<QString, bool>* getInputMap();
    void setInputMap(QMap<QString, bool>* &value);

    //autres methodes
    void moveRight();
    void moveLeft();
    void Jump();
    void spriteUpdater();
    int getPosX();
    int getPosY();
    void moveMario();
};

#endif // MARIO_H
