#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QScrollBar>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QGraphicsView>
#include <QSoundEffect>
#include <QThread>

#include "brick.h"
#include "superbrick.h"
#include "sol.h"
#include "mario.h"
#include "castle.h"
#include "flagEND.h"
#include "pipe.h"
#include "soltrap.h"
#include "spikes.h"
#include "bricktrap.h"
#include "bombetrap.h"
#include "stairs.h"
#include "bulltrap.h"
#include "soundmanager.h"
#include "entity.h"
#include "screenlabel.h"

#define TIMER_REFRESH 17

class Map : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Map(QScrollBar* s, QJsonObject listAll, QObject *parent = 0);
    ~Map();
    QList<QGraphicsItem*> * getGraphicsItem(QString name);
    void collisionMarioTraps();
    void collisionMario();
    static int const Hauteur = 800;
    static int const Longueur = 1200;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void checkGameOver();
    void playSound(QString sound);
    Entity *getMyMario() const;
    void setMyMario(Entity *value);

public slots:
    void Refresh();
    void initScroll();
    void setValueScroll(int value);
    void reset();

private:
    void initPlayField();
    QJsonObject listAll;
    QObject * parent;
    QTimer * m_timer;
    Entity * myMario;
    QScrollBar * scroll;
    SoundManager * soundManager;
    bool gameIsOver = false;
    int deathCounter = 0;
    int loopDeath = 0;
    bool soundPlayed = false;


};

#endif // MAP_H
