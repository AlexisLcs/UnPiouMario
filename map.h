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
#include <QtMath>
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
#include "StairBlock.h"
#include "bulltrap.h"
#include "soundmanager.h"
#include "entity.h"
#include "screenlabel.h"

#define TIMER_REFRESH 17

class Map : public QGraphicsScene
{
    Q_OBJECT
public:
    // Constructeur et destructeur
    explicit Map(QScrollBar* s, QJsonObject listAll, QObject *parent = 0);
    ~Map();

    QList<QGraphicsItem*> * getGraphicsItem(QString name);

    void TriggerBomb();
    // Dimensions de la fenêtre de jeu.
    static int const Hauteur = 800;
    static int const Longueur = 1200;

    Entity *getMyMario() const;
    void setMyMario(Entity *value);
    QList<QGraphicsItem *> getMovingItems();
    void setMovingItems(QList<QGraphicsItem *> value);

    // Méthodes utilitaires
    void moveItems();
    void playSound(QString sound);

    // Verifications d'états.
    void checkWin();
    void checkGameOver();

    // Gestion du clavier
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

    // Gestion des collisions
    void collisionMarioTraps();
    void collisionMario();

public slots:
    void Refresh(); // Méthode de rafraichissement du jeu.
    void initScroll();
    void setValueScroll(int value);
    void reset();

private:
    // Gestion des objets et événements de la map.
    void initPlayField();
    QJsonObject listAll;
    QObject * parent;
    QTimer * m_timer;
    Entity * myMario; // Personnage principal que contrôlera le joueur.
    QList<QGraphicsItem*> movingItems; //item (autre que mario) qui devront bouger
    QList<BombeTrap*> bombTraps; //list de toutes les bombes pour la gestion des trigger
    QScrollBar * scroll;
    SoundManager * soundManager;

    // Position des triggers pour l'état "win".
    int winPosition = 0;
    int castelPosition = 0;

    // Etats du système durant une partie.
    bool gameIsOver = false;
    bool soundPlayed = false;
    bool winChecked = false;

    // Variables utilitaires.
    int deathCounter = 0;
    int loopDeath = 0;
};

#endif // MAP_H
