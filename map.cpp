#include "map.h"


static bool DEV_ON = false;

Map::Map(QScrollBar* s, QJsonObject listAll, QObject *parent): QGraphicsScene(0,0,8000,780, parent), scroll(s)
{
    this->scroll->setValue(0);
    this->scroll->update();
    this->listAll = listAll;
    initPlayField();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Refresh()));

    this->soundManager = new SoundManager();

    m_timer->start(17);
}

Map::~Map()
{
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
        Mario * item = new Mario(this->scroll, listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        this->myMario = new Entity( item);
        listeRetour->append(item);
    }

    if(name == "castle"){
        Castle * item = new Castle(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    if(name == "castleR"){
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

    setSceneRect(0,0,8000,780);

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
    QList<Castle*> * listeCastleRight = (QList<Castle*>*)getGraphicsItem("castleR");



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

    QPixmap pixMario("..\\UnPiouMario\\images\\mario\\marioskate.png");
    this->myMario->getMario()->setPixmap(pixMario);
    this->myMario->getMario()->setPos(this->myMario->getMario()->getPosX(), this->myMario->getMario()->getPosY());
  
    QMap<QString, bool> *inputMap = new QMap<QString, bool>();
    inputMap->insert("Qt::Key_Left", false);
    inputMap->insert("Qt::Key_Right", false);
    inputMap->insert("Qt::Key_Up", false);
  
    this->myMario->getMario()->setInputMap(inputMap);
    addItem(this->myMario->getMario());
    this->myMario->getMario()->setFlag(QGraphicsItem::ItemIsFocusable);
    this->myMario->getMario()->setFocus();


    Q_FOREACH(Castle * castle, *listeCastleRight){
        castle->setPos(castle->getPosX(), castle->getPosY());
        addItem(castle);
    }
}

//getter & setters pour le mario
Entity *Map::getMyMario() const
{
    return myMario;
}

void Map::setMyMario(Entity *value)
{
    myMario = value;
}
void Map::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Left){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Left");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Left", true);
    }

    if(event->key() == Qt::Key_Right){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Right");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Right", true);
    }

    if(event->key() == Qt::Key_Up){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Up");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Up", true);
    }
}

void Map::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Left");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Left", false);
    }

    if(event->key() == Qt::Key_Right){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Right");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Right", false);
    }

}

void Map::Refresh()
{

    //collision
    collisionMario();
    collisionMarioTraps();
    //déplacement
    this->myMario->getMario()->moveMario();
    collisionMario();
    collisionMarioTraps();
    //deplacement bulltrap FELIX

}

void Map::collisionMarioTraps(){
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    foreach(QGraphicsItem *item, items){
        if(Spikes * spike = qgraphicsitem_cast<Spikes *>(item)){
            playSound("spikes");
            spike->setPixMap(spike->getFilename());
        }
        else if(SolTrap * solTrap = qgraphicsitem_cast<SolTrap *>(item)){
            if(this->myMario->getMario()->getPosX() + 40 >= solTrap->getPosX()){
                solTrap->setVisible(false);
                playSound("soltrap");
                this->myMario->getMario()->setIsOnGround(false);
                this->myMario->getMario()->setIsFalling(true);
            }
        }
        else if(BrickTrap * brickTrap = qgraphicsitem_cast<BrickTrap *>(item)){
            if(brickTrap->getActivation() == "all"){
                brickTrap->setPixMap(brickTrap->getFilename());
            }
            else if(brickTrap->getActivation() == "down"){
                    brickTrap->setPixMap(brickTrap->getFilename());
                }
            if(this->myMario->getMario()->getIsJumping() &&
                       ((this->myMario->getMario()->getPosX() + 40 >= brickTrap->getPosX() && (this->myMario->getMario()->getPosX() + 10 <= brickTrap->getPosX() + 50)) ||
                       (this->myMario->getMario()->getPosX() + 10 <= brickTrap->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 40 >= brickTrap->getPosX()))) &&
                       this->myMario->getMario()->getPosY() + 70 >= brickTrap->getPosY() + 50)
            {
                qDebug() << "Tape en bas";
                this->myMario->getMario()->setIsFalling(true);
                this->myMario->getMario()->setIsJumping(false);
                this->myMario->getMario()->resetJump();
                this->myMario->getMario()->setGoRight(true);
                this->myMario->getMario()->setGoLeft(true);
                this->myMario->getMario()->setIsOnGround(false);
            }
            else if((this->myMario->getMario()->getPosX() + 40 >= brickTrap->getPosX() ||
                    this->myMario->getMario()->getPosX() + 10 <= brickTrap->getPosX() + 50) &&
                    this->myMario->getMario()->getPosY() + 70 >= brickTrap->getPosY() &&
                    this->myMario->getMario()->getPosY() + 70 <= brickTrap->getPosY() + 20 &&
                    ((this->myMario->getMario()->getIsFalling()) || (!this->myMario->getMario()->getIsOnGround())))
            {
                qDebug() << "Tape en haut";
                this->myMario->getMario()->setIsFalling(false);
                this->myMario->getMario()->setIsJumping(false);
                this->myMario->getMario()->resetJump();
                this->myMario->getMario()->setGoRight(true);
                this->myMario->getMario()->setGoLeft(true);
                this->myMario->getMario()->setIsOnGround(true);
            }
            else if(this->myMario->getMario()->getPosX() <= brickTrap->getPosX() + 50 &&
                    this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() + 50 &&
                    !this->myMario->getMario()->getIsOnGround())
            {
                qDebug() << "Tape à gauche";
                this->myMario->getMario()->setGoLeft(false);
                this->myMario->getMario()->setGoRight(true);
            }
            else if(this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                    this->myMario->getMario()->getPosX() <= brickTrap->getPosX() &&
                    !this->myMario->getMario()->getIsOnGround())
            {
                qDebug() << "Tape à droite";
                this->myMario->getMario()->setGoRight(false);
                this->myMario->getMario()->setGoLeft(true);
            }
        }
    }
}

void Map::collisionMario(){ //Brick
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    if(items.size() > 0) {
        foreach(QGraphicsItem *item, items){
            if(Pipe * pipe = qgraphicsitem_cast<Pipe *>(item)){
                if((this->myMario->getMario()->getPosX() + 40 >= pipe->getPosX() ||
                        this->myMario->getMario()->getPosX() + 10 <= pipe->getPosX() + 50) &&
                        this->myMario->getMario()->getPosY() + 70 >= pipe->getPosY() &&
                        this->myMario->getMario()->getPosY() + 70 <= pipe->getPosY() + 30 &&
                        ((this->myMario->getMario()->getIsFalling()) || (!this->myMario->getMario()->getIsOnGround()))) // && this->myMario->getMario()->getIsFalling()
                {
                    qDebug() << "Tape en haut";
                    this->myMario->getMario()->setIsFalling(false);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(true);
                }
                else if(this->myMario->getMario()->getPosX() <= pipe->getPosX() + 75 &&
                        this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX() + 75 &&
                        this->myMario->getMario()->getPosY() +70 >= pipe->getPosY() +20)
                {
                    qDebug() << "Tape à gauche";
                    this->myMario->getMario()->setGoLeft(false);
                    this->myMario->getMario()->setGoRight(true);
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX() &&
                        this->myMario->getMario()->getPosX() <= pipe->getPosX() &&
                        this->myMario->getMario()->getPosY() +70 >= pipe->getPosY() +20)
                {
                    qDebug() << "Tape à droite";
                    this->myMario->getMario()->setGoRight(false);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }
            else if(SuperBrick * superBrick = qgraphicsitem_cast<SuperBrick *>(item)){ //SuperBrick
                if(this->myMario->getMario()->getIsJumping() &&
                           ((this->myMario->getMario()->getPosX() + 40 >= superBrick->getPosX() && (this->myMario->getMario()->getPosX() + 10 <= superBrick->getPosX() + 50)) ||
                           (this->myMario->getMario()->getPosX() + 10 <= superBrick->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 40 >= superBrick->getPosX()))) &&
                           this->myMario->getMario()->getPosY() + 70 >= superBrick->getPosY() + 50)
                {
                    this->myMario->getMario()->setIsFalling(true);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(false);
                }
                else if((this->myMario->getMario()->getPosX() + 40 >= superBrick->getPosX() ||
                        this->myMario->getMario()->getPosX() + 10 <= superBrick->getPosX() + 50) &&
                        this->myMario->getMario()->getPosY() + 70 >= superBrick->getPosY() &&
                        this->myMario->getMario()->getPosY() + 70 <= superBrick->getPosY() + 30 &&
                        ((this->myMario->getMario()->getIsFalling()) || (!this->myMario->getMario()->getIsOnGround())))
                {
                    this->myMario->getMario()->setIsFalling(false);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(true);
                }
                else if(this->myMario->getMario()->getPosX() <= superBrick->getPosX() + 50 &&
                        this->myMario->getMario()->getPosX() + 50 >= superBrick->getPosX() + 50 &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    this->myMario->getMario()->setGoLeft(false);
                    this->myMario->getMario()->setGoRight(true);
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= superBrick->getPosX() &&
                        this->myMario->getMario()->getPosX() <= superBrick->getPosX() &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    this->myMario->getMario()->setGoRight(false);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }

            else if(Brick * brick = qgraphicsitem_cast<Brick *>(item)){ //Brick
                if(this->myMario->getMario()->getIsJumping() &&
                           ((this->myMario->getMario()->getPosX() + 40 >= brick->getPosX() && (this->myMario->getMario()->getPosX() + 10 <= brick->getPosX() + 50)) ||
                           (this->myMario->getMario()->getPosX() + 10 <= brick->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 40 >= brick->getPosX()))) &&
                           this->myMario->getMario()->getPosY() + 70 >= brick->getPosY() + 50)
                {
                    this->myMario->getMario()->setIsFalling(true);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(false);
                }
                else if((this->myMario->getMario()->getPosX() + 40 >= brick->getPosX() ||
                        this->myMario->getMario()->getPosX() + 10 <= brick->getPosX() + 50) &&
                        this->myMario->getMario()->getPosY() + 70 >= brick->getPosY() &&
                        this->myMario->getMario()->getPosY() + 70 <= brick->getPosY() + 30 &&
                        ((this->myMario->getMario()->getIsFalling()) || (!this->myMario->getMario()->getIsOnGround())))
                {
                    this->myMario->getMario()->setIsFalling(false);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(true);
                }
                else if(this->myMario->getMario()->getPosX() <= brick->getPosX() + 50 &&
                        this->myMario->getMario()->getPosX() + 50 >= brick->getPosX() + 50 &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    this->myMario->getMario()->setGoLeft(false);
                    this->myMario->getMario()->setGoRight(true);
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= brick->getPosX() &&
                        this->myMario->getMario()->getPosX() <= brick->getPosX() &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    this->myMario->getMario()->setGoRight(false);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }

            else if(Sol * sol = qgraphicsitem_cast<Sol *>(item)){
                if(!this->myMario->getMario()->getIsOnGround()){
                    this->myMario->getMario()->setIsFalling(false);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->setIsOnGround(true);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }
        }
    } else {
        this->myMario->getMario()->setIsOnGround(false);
        this->myMario->getMario()->setGoRight(true);
        this->myMario->getMario()->setGoLeft(true);
    }
}

void Map::playSound(QString sound){
    if(sound == "spikes"){
        this->soundManager->spikes.play();
    }
    else if(sound == "soltrap"){
        this->soundManager->soltrap.play();
    }
}

void Map::initScroll(){
    this->scroll->setValue(0);
}

void Map::setValueScroll(int value){
    this->scroll->setValue(value);
}

