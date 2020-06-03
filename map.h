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
    void playSound(QString sound);
    Entity *getMyMario() const;
    void setMyMario(Entity *value);

public slots:
    void Refresh();

private:
    void initPlayField();
    QJsonObject listAll;
    QScrollBar * scroll;
    QTimer * m_timer;
    Entity * myMario;
    SoundManager * soundManager;


};

#endif // MAP_H
