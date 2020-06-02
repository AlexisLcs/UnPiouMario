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

class Map : public QGraphicsScene
{
public:
    explicit Map(QScrollBar* s, QJsonObject listAll, QObject *parent = 0);
    QList<QGraphicsItem*> * getGraphicsItem(QString name);
    void timerEvent(QTimerEvent *);
    void collisionMario();
    static int const Hauteur = 800;
    static int const Longueur = 1200;
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void playSound(QString sound);
    void initScroll();
    void setValueScroll(int value);

private:
    void initPlayField();
    QJsonObject listAll;
    QTimer * m_timer;
    Entity * myMario;
    QScrollBar * scroll;
    SoundManager * soundManager;


};

#endif // MAP_H
