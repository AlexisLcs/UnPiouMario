#include "map.h"


static bool DEV_ON = false;

Map::Map(QScrollBar* s, QJsonObject listAll, QObject *parent): QGraphicsScene(0,0,8000,790, parent)
{
    this->scroll = s;
    this->listAll = listAll;
    initPlayField();
    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    this->soundManager = new SoundManager();
}

QList<QGraphicsItem*> * Map::getGraphicsItem(QString name){
    QJsonObject listeObject = this->listAll[name].toObject();


    QList<QGraphicsItem*> * listeRetour = new QList<QGraphicsItem*>();

    if(name == "sol"){
        Q_FOREACH(QJsonValue sol, listeObject){
            Sol * item = new Sol(sol["length"].toString().toInt(), sol["image"].toString(), sol["posX"].toString().toInt(), sol["posY"].toString().toInt(), sol["visible"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "stairs"){
        Q_FOREACH(QJsonValue stairs, listeObject){
            Stairs * item = new Stairs(stairs["length"].toString().toInt(), stairs["image"].toString(), stairs["posX"].toString().toInt(), stairs["posY"].toString().toInt(), stairs["size"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "soltrap"){
        Q_FOREACH(QJsonValue soltrap, listeObject){
            SolTrap * item = new SolTrap(soltrap["length"].toString().toInt(), soltrap["image"].toString(), soltrap["posX"].toString().toInt(), soltrap["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "bricks"){
        Q_FOREACH(QJsonValue brick, listeObject){
            Brick * item = new Brick(brick["length"].toString().toInt(), brick["image"].toString(), brick["posX"].toString().toInt(), brick["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "brickstrap"){
        Q_FOREACH(QJsonValue brickstrap, listeObject){
            BrickTrap * item = new BrickTrap(brickstrap["length"].toString().toInt(), brickstrap["image"].toString(), brickstrap["posX"].toString().toInt(), brickstrap["posY"].toString().toInt(), brickstrap["activation"].toString());
            listeRetour->append(item);
        }
    }

    if(name == "superbricks"){
        Q_FOREACH(QJsonValue superbrick, listeObject){
            SuperBrick * item = new SuperBrick(superbrick["length"].toString().toInt(), superbrick["image"].toString(), superbrick["posX"].toString().toInt(), superbrick["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "pipe"){
        Q_FOREACH(QJsonValue pipe, listeObject){
            Pipe * item = new Pipe(pipe["length"].toString().toInt(), pipe["image"].toString(), pipe["posX"].toString().toInt(), pipe["posY"].toString().toInt(), pipe["size"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "bombstrap"){
        Q_FOREACH(QJsonValue bomb, listeObject){
            BombeTrap * item = new BombeTrap(bomb["length"].toString().toInt(), bomb["image"].toString(), bomb["posX"].toString().toInt(), bomb["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "spikes"){
        Q_FOREACH(QJsonValue spikes, listeObject){
            Spikes * item = new Spikes(spikes["length"].toString().toInt(), spikes["image"].toString(), spikes["posX"].toString().toInt(), spikes["posY"].toString().toInt(), spikes["direction"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "bulltrap"){
        Q_FOREACH(QJsonValue bull, listeObject){
            BullTrap * item = new BullTrap(bull["length"].toString().toInt(), bull["imageL"].toString(), bull["imageR"].toString(), bull["posX"].toString().toInt(), bull["posY"].toString().toInt(), bull["direction"].toString().toInt());
            listeRetour->append(item);
        }
    }

    if(name == "mario"){
        Mario * item = new Mario(listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        this->myMario = new Entity(item);
        listeRetour->append(item);
    }

    if(name == "castle"){
        Castle * item = new Castle(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    if(name == "flagEND"){
        FlagEND * item = new FlagEND(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    return listeRetour;
}


void Map::initPlayField(){
    qDebug() << "init map";

    setSceneRect(0,0,8000,790);

    QList<Sol*> * listSols = (QList<Sol*>*)getGraphicsItem("sol");
    QList<Brick*> * listBricks = (QList<Brick*>*)getGraphicsItem("bricks");
    QList<SuperBrick*> * listSuperBricks = (QList<SuperBrick*>*)getGraphicsItem("superbricks");
    QList<Mario*> * listeMario = (QList<Mario*>*)getGraphicsItem("mario");
    QList<Castle*> * listeCastle = (QList<Castle*>*)getGraphicsItem("castle");
    QList<FlagEND*> * listeFlagEND = (QList<FlagEND*>*)getGraphicsItem("flagEND");
    QList<Pipe*> * listePipeLit = (QList<Pipe*>*)getGraphicsItem("pipe");
    QList<SolTrap*> * listeSolTrap = (QList<SolTrap*>*)getGraphicsItem("soltrap");
    QList<Spikes*> * listeSpikes = (QList<Spikes*>*)getGraphicsItem("spikes");
    QList<BrickTrap*> * listBricksTraps = (QList<BrickTrap*>*)getGraphicsItem("brickstrap");
    QList<BombeTrap*> * listBombesTraps = (QList<BombeTrap*>*)getGraphicsItem("bombstrap");
    QList<Stairs*> * listStairs = (QList<Stairs*>*)getGraphicsItem("stairs");
    QList<BullTrap*> * listBullTrap = (QList<BullTrap*>*)getGraphicsItem("bulltrap");

    Q_FOREACH(Sol * sol, *listSols){
        sol->setPos(sol->getPosX(), sol->getPosY());
        addItem(sol);
        if(sol->isVisible() == 1){
            sol->setVisible(DEV_ON);
        }
    }

    Q_FOREACH(Stairs * stairs, *listStairs){
        stairs->setPos(stairs->getPosX(), stairs->getPosY());
        addItem(stairs);
    }

    Q_FOREACH(SolTrap * solTrap, *listeSolTrap){
        solTrap->setPos(solTrap->getPosX(), solTrap->getPosY());
        addItem(solTrap);
    }

    Q_FOREACH(Spikes * spikes, *listeSpikes){
        spikes->setPos(spikes->getPosX(), spikes->getPosY());
        addItem(spikes);
        //spikes->hide();
    }

    Q_FOREACH(Brick * brick, *listBricks){
        brick->setPos(brick->getPosX(), brick->getPosY());
        addItem(brick);
    }

    Q_FOREACH(BrickTrap * bricktrap, *listBricksTraps){
        bricktrap->setPos(bricktrap->getPosX(), bricktrap->getPosY());
        addItem(bricktrap);
    }

    Q_FOREACH(BombeTrap * bombe, *listBombesTraps){
        bombe->setPos(bombe->getPosX(), bombe->getPosY());
        addItem(bombe);
        bombe->setVisible(DEV_ON);
    }

    Q_FOREACH(SuperBrick * superbricks, *listSuperBricks){
        superbricks->setPos(superbricks->getPosX(), superbricks->getPosY());
        addItem(superbricks);
    }

    Q_FOREACH(Pipe * pipe, *listePipeLit){
        pipe->setPos(pipe->getPosX(), pipe->getPosY());
        addItem(pipe);
    }

    Q_FOREACH(Castle * castle, *listeCastle){
        castle->setPos(castle->getPosX(), castle->getPosY());
        addItem(castle);
    }

    Q_FOREACH(FlagEND * flagend, *listeFlagEND){
        flagend->setPos(flagend->getPosX(), flagend->getPosY());
        addItem(flagend);
    }

    Q_FOREACH(BullTrap * bullTrap, *listBullTrap){
        bullTrap->setPos(bullTrap->getPosX(), bullTrap->getPosY());
        addItem(bullTrap);
        qDebug() << bullTrap;
    }

    QPixmap pixMario("..\\UnPiouMario\\images\\mario\\mario_stop.png");
    this->myMario->getMario()->setPixmap(pixMario);
    this->myMario->getMario()->setPos(this->myMario->getMario()->getPosX(), this->myMario->getMario()->getPosY());
    addItem(this->myMario->getMario());
    this->myMario->getMario()->setFlag(QGraphicsItem::ItemIsFocusable);
    this->myMario->getMario()->setFocus();

    qDebug() << "init ok";
}


void Map::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Left){

        this->myMario->getMario()->moveLeft();
        this->myMario->getMario()->getInputMap()[Qt::Key_Left] = true;

        collisionMario();

    }

    if(event->key() == Qt::Key_Right){
        this->myMario->getMario()->moveRight();
        this->myMario->getMario()->getInputMap()[Qt::Key_Right] = true;

        collisionMario();
    }

    if(event->key() == Qt::Key_Up){
        this->myMario->getMario()->Jump();
        this->myMario->getMario()->getInputMap()[Qt::Key_Up] = true;

        collisionMario();
    }
}

void Map::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        this->myMario->getMario()->getInputMap()[Qt::Key_Left] = false;

    if(event->key() == Qt::Key_Right)
        this->myMario->getMario()->getInputMap()[Qt::Key_Right] = false;

    if(event->key() == Qt::Key_Up)
        this->myMario->getMario()->getInputMap()[Qt::Key_Up] = false;

}


void Map::collisionMarioTraps(){
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    foreach(QGraphicsItem *item, items){
        if(Spikes * spike = qgraphicsitem_cast<Spikes *>(item)){
            playSound("spikes");
            spike->setPixMap(spike->getFilename());
        }
        else if(SolTrap * solTrap = qgraphicsitem_cast<SolTrap *>(item)){
            solTrap->setVisible(false);
        }
        else if(BrickTrap * brickTrap = qgraphicsitem_cast<BrickTrap *>(item)){
            if(brickTrap->getActivation() == "all"){
                brickTrap->setPixMap(brickTrap->getFilename());
            }
            else if(brickTrap->getActivation() == "down" && this->myMario->getMario()->getIsJumping()){
                if((this->myMario->getMario()->getPosY() <= brickTrap->getPosY() + 50 && this->myMario->getMario()->getPosY() >=  brickTrap->getPosY() + 45) &&
                        (this->myMario->getMario()->getPosX() >= brickTrap->getPosX() || this->myMario->getMario()->getPosX() + 50 <= brickTrap->getPosX() + 50) ){
                    brickTrap->setPixMap(brickTrap->getFilename());
                }
            }
        }
    }
}

void Map::collisionMario(){
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    foreach(QGraphicsItem *item, items){
        if(Pipe * pipe = qgraphicsitem_cast<Pipe *>(item)){
            //Tape bord droit du Pipe
            qDebug() << "this->myMario->getMario()->getPosX()" << this->myMario->getMario()->getPosX();
            qDebug() << "this->myMario->getMario()->getPosX() + 50" << this->myMario->getMario()->getPosX() + 50;
            qDebug() << "this->myMario->getMario()->getPosY()" << this->myMario->getMario()->getPosY();
            qDebug() << "this->myMario->getMario()->getPosY() + 55" << this->myMario->getMario()->getPosY() + 55;
            qDebug() << "pipe->getPosX()" << pipe->getPosX();
            qDebug() << "pipe->getPosX() + 50" << pipe->getPosX() + 75;
            qDebug() << "pipe->getPosY()" << pipe->getPosY();
            qDebug() << "pipe->getPosY() + 55" << pipe->getPosY() + 55;
            if((this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX()) && (this->myMario->getMario()->getPosX() <= pipe->getPosX() + 75) && !(this->myMario->getMario()->getIsFalling())){
                if(this->myMario->getMario()->getIsLooking()){
                    this->myMario->getMario()->setGoRight(false);
                }
                else {
                    this->myMario->getMario()->setGoLeft(false);
                }
            }
            else if((this->myMario->getMario()->getPosX() >= pipe->getPosX()) && (this->myMario->getMario()->getPosX() +50 <= pipe->getPosX() + 75) && (this->myMario->getMario()->getPosY() + 55 >= pipe->getPosY())){
                this->myMario->getMario()->setIsFalling(false);
                this->myMario->getMario()->setIsJumping(false);
                this->myMario->getMario()->setGoRight(true);
                this->myMario->getMario()->setGoLeft(true);
                this->myMario->getMario()->resetJump();
            }
        }

        if(Sol * sol = qgraphicsitem_cast<Sol *>(item)){
            this->myMario->getMario()->setIsFalling(false);
            this->myMario->getMario()->setIsJumping(false);
            this->myMario->getMario()->resetJump();
        }
        else if(Spikes * spike = qgraphicsitem_cast<Spikes *>(item)){
            this->myMario->getMario()->setIsFalling(false);
            this->myMario->getMario()->setIsJumping(false);
        }
        else if(Pipe * pipe = qgraphicsitem_cast<Pipe *>(item)){

        }
        else {
            this->myMario->getMario()->setPos(this->myMario->getMario()->getPosX(),this->myMario->getMario()->getPosY()+this->myMario->getMario()->getVelocity()[1]);
        }
    }
}

void Map::playSound(QString sound){
    if(sound == "spikes"){
        this->soundManager->spikes.play();
    }
}

void Map::timerEvent(QTimerEvent *){

}
