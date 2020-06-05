#include "map.h"

// Mode développeur pour les tests.
static bool DEV_ON = false;

// Constructeur initialisant les composants principaux et démarrant la boucle de rafraichissement du jeu.
Map::Map(QScrollBar* s, QJsonObject listAll, QObject *parent): QGraphicsScene(0,0,8000,780, parent), scroll(s)
{
    this->parent = parent;
    this->scroll->setValue(0);
    this->scroll->update();
    this->listAll = listAll;

    this->soundManager = new SoundManager(); // Création d'un objet de gestion des bruitages.
    initPlayField(); // Initialisation de tous les objets de la carte.

    // Création du Timer.
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Refresh()));
    m_timer->start(TIMER_REFRESH);

}

Map::~Map()
{
}

// Méthode permettant la récupération des données Json liées aux objets graphiques.
QList<QGraphicsItem*> * Map::getGraphicsItem(QString name){
    QJsonObject listeObject = this->listAll[name].toObject();
    QList<QGraphicsItem*> * listeRetour = new QList<QGraphicsItem*>();

    // Lecture des objets liés au sol.
    if(name == "sol"){
        Q_FOREACH(QJsonValue sol, listeObject){
            Sol * item = new Sol(sol["length"].toString().toInt(), sol["image"].toString(), sol["posX"].toString().toInt(), sol["posY"].toString().toInt(), sol["visible"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux sols piégés.
    if(name == "soltrap"){
        Q_FOREACH(QJsonValue soltrap, listeObject){
            SolTrap * item = new SolTrap(soltrap["length"].toString().toInt(), soltrap["image"].toString(), soltrap["posX"].toString().toInt(), soltrap["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux bricks.
    if(name == "bricks"){
        Q_FOREACH(QJsonValue brick, listeObject){
            Brick * item = new Brick(brick["length"].toString().toInt(), brick["image"].toString(), brick["posX"].toString().toInt(), brick["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux bricks piégées.
    if(name == "brickstrap"){
        Q_FOREACH(QJsonValue brickstrap, listeObject){
            BrickTrap * item = new BrickTrap(brickstrap["length"].toString().toInt(), brickstrap["image"].toString(), brickstrap["posX"].toString().toInt(), brickstrap["posY"].toString().toInt(), brickstrap["activation"].toString(), brickstrap["cangoon"].toString());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux superbricks.
    if(name == "superbricks"){
        Q_FOREACH(QJsonValue superbrick, listeObject){
            SuperBrick * item = new SuperBrick(superbrick["length"].toString().toInt(), superbrick["image"].toString(), superbrick["posX"].toString().toInt(), superbrick["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux pipes.
    if(name == "pipe"){
        Q_FOREACH(QJsonValue pipe, listeObject){
            Pipe * item = new Pipe(pipe["length"].toString().toInt(), pipe["image"].toString(), pipe["posX"].toString().toInt(), pipe["posY"].toString().toInt(), pipe["size"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux bombes.
    if(name == "bombstrap"){
        Q_FOREACH(QJsonValue bomb, listeObject){
            BombeTrap * item = new BombeTrap(bomb["length"].toString().toInt(), bomb["image"].toString(), bomb["posX"].toString().toInt(), bomb["posY"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés aux pics.
    if(name == "spikes"){
        Q_FOREACH(QJsonValue spikes, listeObject){
            Spikes * item = new Spikes(spikes["length"].toString().toInt(), spikes["image"].toString(), spikes["posX"].toString().toInt(), spikes["posY"].toString().toInt(), spikes["direction"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés au bulltrap supersonic.
    if(name == "bulltrap"){
        Q_FOREACH(QJsonValue bull, listeObject){
            BullTrap * item = new BullTrap(bull["length"].toString().toInt(), bull["imageL"].toString(), bull["imageR"].toString(), bull["posX"].toString().toInt(), bull["posY"].toString().toInt(), bull["direction"].toString().toInt());
            listeRetour->append(item);
        }
    }

    // Lecture des objets liés au personnage principal.
    if(name == "mario"){
        Mario * item = new Mario(this->scroll, listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        this->myMario = new Entity( item);
        listeRetour->append(item);
    }

    // Lecture des objets liés au chateau de fin de niveau (première partie).
    if(name == "castle"){
        Castle * item = new Castle(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    // Lecture des objets liés au chateau de fin de niveau (deuxième partie).
    if(name == "castleR"){
        Castle * item = new Castle(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    // Lecture des objets liés au drapeau de fin de niveau.
    if(name == "flagEND"){
        FlagEND * item = new FlagEND(listeObject["length"].toString().toInt(), listeObject["image"].toString(), listeObject["posX"].toString().toInt(), listeObject["posY"].toString().toInt());
        listeRetour->append(item);
    }

    return listeRetour;
}


// Méthode d'initialisation des objets de la carte.
void Map::initPlayField(){

    setSceneRect(0,0,8000,780); // Dimension du niveau.
    // Récupération des objets graphiques.
    QList<Sol*> * listSols = (QList<Sol*>*)getGraphicsItem("sol");
    QList<Brick*> * listBricks = (QList<Brick*>*)getGraphicsItem("bricks");
    QList<SuperBrick*> * listSuperBricks = (QList<SuperBrick*>*)getGraphicsItem("superbricks");
    getGraphicsItem("mario");
    QList<Castle*> * listeCastle = (QList<Castle*>*)getGraphicsItem("castle");
    QList<FlagEND*> * listeFlagEND = (QList<FlagEND*>*)getGraphicsItem("flagEND");
    QList<Pipe*> * listePipeLit = (QList<Pipe*>*)getGraphicsItem("pipe");
    QList<SolTrap*> * listeSolTrap = (QList<SolTrap*>*)getGraphicsItem("soltrap");
    QList<Spikes*> * listeSpikes = (QList<Spikes*>*)getGraphicsItem("spikes");
    QList<BrickTrap*> * listBricksTraps = (QList<BrickTrap*>*)getGraphicsItem("brickstrap");
    QList<BombeTrap*> * listBombesTraps = (QList<BombeTrap*>*)getGraphicsItem("bombstrap");
    QList<BullTrap*> * listBullTrap = (QList<BullTrap*>*)getGraphicsItem("bulltrap");
    QList<Castle*> * listeCastleRight = (QList<Castle*>*)getGraphicsItem("castleR");


    // Initialisation des objets sur la scene.
    Q_FOREACH(Sol * sol, *listSols){
        sol->setPos(sol->getPosX(), sol->getPosY());
        addItem(sol);
    }

    Q_FOREACH(SolTrap * solTrap, *listeSolTrap){
        solTrap->setPos(solTrap->getPosX(), solTrap->getPosY());
        addItem(solTrap);
    }

    Q_FOREACH(Spikes * spikes, *listeSpikes){
        spikes->setPos(spikes->getPosX(), spikes->getPosY());
        addItem(spikes);
    }

    Q_FOREACH(Brick * brick, *listBricks){
        brick->setPos(brick->getPosX(), brick->getPosY());
        addItem(brick);
    }

    Q_FOREACH(BrickTrap * bricktrap, *listBricksTraps){
        bricktrap->setPos(bricktrap->getPosX(), bricktrap->getPosY());
        addItem(bricktrap);
    }

    this->bombTraps = *listBombesTraps;
    Q_FOREACH(BombeTrap * bombe, *listBombesTraps){
        bombe->setPos(bombe->getPosX(), bombe->getPosY());
        addItem(bombe);
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
        winPosition = flagend->getPosX();
        addItem(flagend);
    }

    Q_FOREACH(BullTrap * bullTrap, *listBullTrap){
        bullTrap->setPos(bullTrap->getPosX(), bullTrap->getPosY());
        addItem(bullTrap);
        movingItems.append(bullTrap); //ajout du bulltrap dans les movingitems
    }

    Q_FOREACH(Castle * castle, *listeCastleRight){
        castle->setPos(castle->getPosX(), castle->getPosY());
        castelPosition = castle->getPosX(); // Récupération de la position du chateau de fin.
        addItem(castle);
    }

    ScreenLabel * item = new ScreenLabel();


    /* Initialisation du compteur de mort */
    item->setPos(20, 5);
    item->setPlainText("Nb. de morts : " + QString::number(deathCounter));
    item->setDefaultTextColor(Qt::white);
    item->setScale(2);
    item->setVisible(true);

    addItem(item);

    this->myMario->getMario()->setCounter(item);

    // Initialisation du personnage principal.
    QPixmap pixMario("..\\UnPiouMario\\images\\mario\\marioskate.png");
    this->myMario->getMario()->setPixmap(pixMario);
    this->myMario->getMario()->setPos(this->myMario->getMario()->getPosX(), this->myMario->getMario()->getPosY());
  
    // Initialisation de l'état par défaut des touches du clavier.
    QMap<QString, bool> *inputMap = new QMap<QString, bool>();
    inputMap->insert("Qt::Key_Left", false);
    inputMap->insert("Qt::Key_Right", false);
    inputMap->insert("Qt::Key_Up", false);

    this->myMario->getMario()->setInputMap(inputMap);

    addItem(this->myMario->getMario()); // Ajout du mario à la scene.

    // Activation du focus sur le mario.
    this->myMario->getMario()->setFlag(QGraphicsItem::ItemIsFocusable);
    this->myMario->getMario()->setFocus();

    this->soundManager->musique.play(); // Activation de la soundtrack.
}

QList<QGraphicsItem *> Map::getMovingItems()
{
    return movingItems;
}
void Map::setMovingItems(QList<QGraphicsItem *> value)
{
    movingItems = value;
}

// Permet de gérer le déplacement des ennemis.
void Map::moveItems()
{
    foreach(QGraphicsItem* item, movingItems)
    {
        if(BullTrap * bulltrap = qgraphicsitem_cast<BullTrap *>(item))
            if(bulltrap->getMove()){
                bulltrap->moveBullTrap();
            }
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

// Méthode de gestion des touches du clavier.
void Map::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Left && !gameIsOver){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Left");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Left", true);
    }

    if(event->key() == Qt::Key_Right && !gameIsOver){
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Right");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Right", true);
    }

    if(event->key() == Qt::Key_Up && this->myMario->getMario()->getIsOnGround() && !gameIsOver){
        playSound("jump");
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Up");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Up", true);
    }
}

// Méthode permettant de réinitialiser l'état des touches du clavier.
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

// Méthode de rafraichissement du jeu permettant de gérer les collisions, les mouvements ou encore l'état de la partie.
void Map::Refresh()
{

    //collision
    collisionMario();
    if(!DEV_ON){
        collisionMarioTraps();
    }

    //déplacement des moving items
    moveItems();

    //gestion des bombs
    //cela se fait ici car il n'y a pas de collisions directe avec les bombes.
    TriggerBomb();

    // Check Game Over
    checkGameOver();

    // Check Win
    checkWin();

    //déplacement
    this->myMario->getMario()->moveMario();
}

// Gestion des collisions avec les pièges de la scene.
void Map::collisionMarioTraps(){
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    foreach(QGraphicsItem *item, items){

        // Collisions avec les pics.
        if(Spikes * spike = qgraphicsitem_cast<Spikes *>(item)){
            if(this->myMario->getMario()->getPosX() + 35 >= spike->getPosX() && !spike->getIsActivated()){
                spike->setPixMap(spike->getFilename());
                spike->setIsActivated(true);
                playSound("spikes");
                // GAME OVER
                gameIsOver = true;
            }
        }

        // Collisions avec les sols piégés.
        else if(SolTrap * solTrap = qgraphicsitem_cast<SolTrap *>(item)){
            if(this->myMario->getMario()->getPosX() + 40 >= solTrap->getPosX()){
                solTrap->setVisible(false);
                this->myMario->getMario()->setIsOnGround(false);
                this->myMario->getMario()->setIsFalling(true);
            }
        }

        // Collisions avec les briques piégées.
        else if(BrickTrap * brickTrap = qgraphicsitem_cast<BrickTrap *>(item)){
            if(brickTrap->getActivation() == "all"){ // Briques paramétrées pour une collision totale (tout autour).
                if(!brickTrap->getIsActivated()){
                    brickTrap->setPixMap(brickTrap->getFilename());
                    brickTrap->setIsActivated(true);
                }
                if(this->myMario->getMario()->getIsJumping() &&
                           ((this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() && (this->myMario->getMario()->getPosX() <= brickTrap->getPosX() + 50)) ||
                           (this->myMario->getMario()->getPosX()<= brickTrap->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX()))) &&
                           this->myMario->getMario()->getPosY() + 70 >= brickTrap->getPosY() + 50)
                {
                    if(brickTrap->getIsActivated()){
                        brickTrap->setPixMap(brickTrap->getFilename());
                        playSound("bip");
                        this->myMario->getMario()->setIsFalling(true);
                        this->myMario->getMario()->setIsJumping(false);
                        this->myMario->getMario()->resetJump();
                        this->myMario->getMario()->setGoRight(true);
                        this->myMario->getMario()->setGoLeft(true);
                        this->myMario->getMario()->setIsOnGround(false);
                    }
                }
                else if(brickTrap->getCanGoOn() && this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                        this->myMario->getMario()->getPosX()<= brickTrap->getPosX() + 50 &&
                        this->myMario->getMario()->getPosY() + 70 <= brickTrap->getPosY() + 50 &&
                        (this->myMario->getMario()->getIsFalling() || !this->myMario->getMario()->getIsOnGround()))
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setIsFalling(false);
                        this->myMario->getMario()->setIsJumping(false);
                        this->myMario->getMario()->resetJump();
                        this->myMario->getMario()->setGoRight(true);
                        this->myMario->getMario()->setGoLeft(true);
                        this->myMario->getMario()->setIsOnGround(true);
                    }
                }
                else if(this->myMario->getMario()->getPosX() <= brickTrap->getPosX() + 50 &&
                        this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() + 50 &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setGoLeft(false);
                        this->myMario->getMario()->setGoRight(true);
                    }
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                        this->myMario->getMario()->getPosX() <= brickTrap->getPosX() &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setGoRight(false);
                        this->myMario->getMario()->setGoLeft(true);
                    }
                }
            }
            else if(brickTrap->getActivation() == "down") // Briques paramétrées pour une collision uniquement d'en dessous.
            {
                if(this->myMario->getMario()->getIsJumping() &&
                   this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                   this->myMario->getMario()->getPosX() <= brickTrap->getPosX() + 50 &&
                   this->myMario->getMario()->getPosY() + 70 >= brickTrap->getPosY() + 50)
                {
                    if(brickTrap->getActivation() == "down" && !brickTrap->getIsActivated()){
                        brickTrap->setPixMap(brickTrap->getFilename());
                        brickTrap->setIsActivated(true);
                    }
                    if(brickTrap->getIsActivated()){
                        brickTrap->setPixMap(brickTrap->getFilename());
                        playSound("bip");
                        this->myMario->getMario()->setIsFalling(true);
                        this->myMario->getMario()->setIsJumping(false);
                        this->myMario->getMario()->resetJump();
                        this->myMario->getMario()->setGoRight(true);
                        this->myMario->getMario()->setGoLeft(true);
                        this->myMario->getMario()->setIsOnGround(false);
                    }
                }
                else if(brickTrap->getCanGoOn() && this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                        this->myMario->getMario()->getPosX()<= brickTrap->getPosX() + 50 &&
                        this->myMario->getMario()->getPosY() + 70 <= brickTrap->getPosY() + 50 &&
                        (this->myMario->getMario()->getIsFalling() || !this->myMario->getMario()->getIsOnGround()))
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setIsFalling(false);
                        this->myMario->getMario()->setIsJumping(false);
                        this->myMario->getMario()->resetJump();
                        this->myMario->getMario()->setGoRight(true);
                        this->myMario->getMario()->setGoLeft(true);
                        this->myMario->getMario()->setIsOnGround(true);
                    }
                }
                else if(this->myMario->getMario()->getPosX() <= brickTrap->getPosX() + 50 &&
                        this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() + 50 &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setGoLeft(false);
                        this->myMario->getMario()->setGoRight(true);
                    }
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= brickTrap->getPosX() &&
                        this->myMario->getMario()->getPosX() <= brickTrap->getPosX() &&
                        !this->myMario->getMario()->getIsOnGround())
                {
                    if(brickTrap->getIsActivated()){
                        this->myMario->getMario()->setGoRight(false);
                        this->myMario->getMario()->setGoLeft(true);
                    }
                }
                else if (!brickTrap->getIsActivated()){
                    this->myMario->getMario()->setIsOnGround(false);
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }
        }

        // Collisions avec le bullTrap.
        else if(BullTrap * bullTrap = qgraphicsitem_cast<BullTrap *>(item)){
            // GAME OVER
            gameIsOver = true;
            playSound("bulltrap");
            bullTrap->setMove(false);
        }

        // Collisions avec les bombes.
        else if(BombeTrap * bombTrap = qgraphicsitem_cast<BombeTrap *>(item)){
            // GAME OVER
            gameIsOver = true;
            playSound("explosion");
            bombTrap->setVisible(false);
        }
    }
}

// Gestion des collisions avec l'environnement.
void Map::collisionMario(){
    QList<QGraphicsItem*> items =  collidingItems(this->myMario->getMario());
    if(items.size() > 0) {
        foreach(QGraphicsItem *item, items){

            // Collisions avec les pipes.
            if(Pipe * pipe = qgraphicsitem_cast<Pipe *>(item)){
                if((this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX() ||
                        this->myMario->getMario()->getPosX() <= pipe->getPosX() + 75) &&
                        this->myMario->getMario()->getPosY() + 70 >= pipe->getPosY() &&
                        this->myMario->getMario()->getPosY() + 70 <= pipe->getPosY() + 50 &&
                        ((this->myMario->getMario()->getIsFalling()) || (!this->myMario->getMario()->getIsOnGround()))) // && this->myMario->getMario()->getIsFalling()
                {
                    this->myMario->getMario()->setIsFalling(false);
                    this->myMario->getMario()->setIsJumping(false);
                    this->myMario->getMario()->resetJump();
                    this->myMario->getMario()->setGoRight(true);
                    this->myMario->getMario()->setGoLeft(true);
                    this->myMario->getMario()->setIsOnGround(true);
                }
                else if(this->myMario->getMario()->getPosX() <= pipe->getPosX() + 75 &&
                        this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX() + 75 &&
                        this->myMario->getMario()->getPosY() + 70 >= pipe->getPosY() +20)
                {
                    this->myMario->getMario()->setGoLeft(false);
                    this->myMario->getMario()->setGoRight(true);
                }
                else if(this->myMario->getMario()->getPosX() + 50 >= pipe->getPosX() &&
                        this->myMario->getMario()->getPosX() <= pipe->getPosX() &&
                        this->myMario->getMario()->getPosY() + 70 >= pipe->getPosY() +20)
                {
                    this->myMario->getMario()->setGoRight(false);
                    this->myMario->getMario()->setGoLeft(true);
                }
            }

            // Collisions avec les super briques.
            else if(SuperBrick * superBrick = qgraphicsitem_cast<SuperBrick *>(item)){ //SuperBrick
                if(this->myMario->getMario()->getIsJumping() &&
                           ((this->myMario->getMario()->getPosX() + 40 >= superBrick->getPosX() && (this->myMario->getMario()->getPosX() + 10 <= superBrick->getPosX() + 50)) ||
                           (this->myMario->getMario()->getPosX() + 10 <= superBrick->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 40 >= superBrick->getPosX()))) &&
                           this->myMario->getMario()->getPosY() + 70 >= superBrick->getPosY() + 50)
                {
                    playSound("bip");
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

            // Collisions avec les briques.
            else if(Brick * brick = qgraphicsitem_cast<Brick *>(item)){ //Brick
                if(this->myMario->getMario()->getIsJumping() &&
                 ((this->myMario->getMario()->getPosX() + 40 >= brick->getPosX() && (this->myMario->getMario()->getPosX() + 10 <= brick->getPosX() + 50)) ||
                  (this->myMario->getMario()->getPosX() + 10 <= brick->getPosX() + 50 && (this->myMario->getMario()->getPosX() + 40 >= brick->getPosX()))) &&
                   this->myMario->getMario()->getPosY() + 70 >= brick->getPosY() + 25)
                {
                    playSound("bip");
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
                        this->myMario->getMario()->getPosY() + 70 <= brick->getPosY() + 25 &&
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

            // Collisions avec le sol.
            else if(Sol * sol = qgraphicsitem_cast<Sol *>(item)){
                (void)sol;
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
    }
    else {
        this->myMario->getMario()->setIsOnGround(false);
        this->myMario->getMario()->setGoRight(true);
        this->myMario->getMario()->setGoLeft(true);
    }

}


//trigger pour la gestion des bombes
void Map::TriggerBomb()
{
    foreach(BombeTrap* bomb, bombTraps)
    {
        if((myMario->getMario()->getPosX() + 30 >= bomb->getPosX())){
            if(!bomb->getIsFalling()){
                bomb->setIsFalling(true);
                playSound("fallbomb");
            }
        }

        bomb->FallBomb();
    }
}

// Méthode permettant de réinitialiser la partie.
void Map::reset() {
    QList<QGraphicsItem *> itemList = items();

    /* Reset all items */
    Q_FOREACH(QGraphicsItem * item, itemList) {
        removeItem(item);
    }

    /* Generate a new scene */
    initPlayField();
    setValueScroll(0);

    soundPlayed = false;
}

// Permet de vérifier si le joueur a perdu.
void Map::checkGameOver() {

    // Le joueur a perdu s'il tombe dans un trou.
    if(this->myMario->getMario()->getPosY() > 750){
        this->soundManager->gameovermario.play();
        playSound("soltrap");
        playSound("gameover");
        gameIsOver = true;
    }

    // Gestion de la fenêtre en cas de game over.
    if(gameIsOver){
        this->soundManager->musique.stop();

        // Initialisation des composants du game over à la première itération de la boucle d'attente.
        if(loopDeath == 0) {
            // Titre "GAME OVER"

            QPixmap * gameoverpixmap = new QPixmap("..\\UnPiouMario\\images\\gameover.png");
            QGraphicsPixmapItem * pixGameover = new QGraphicsPixmapItem(*gameoverpixmap, nullptr);
            pixGameover->setPos(scroll->value() + 140, 336);

            addItem(pixGameover);

            // Bloquage des entrées du clavier.
            this->myMario->getMario()->getInputMap()->remove("Qt::Key_Up");
            this->myMario->getMario()->getInputMap()->insert("Qt::Key_Up", false);
            this->myMario->getMario()->getInputMap()->remove("Qt::Key_Left");
            this->myMario->getMario()->getInputMap()->insert("Qt::Key_Left", false);
            this->myMario->getMario()->getInputMap()->remove("Qt::Key_Right");
            this->myMario->getMario()->getInputMap()->insert("Qt::Key_Right", false);
        }
        ++loopDeath;
    }
    if(loopDeath > 2500/TIMER_REFRESH) { // Patiente quelques secondes avant de recréer le niveau.
        ++deathCounter; // Incrémente le compteur du nombre de morts.
        loopDeath = 0;
        gameIsOver = false;
        reset(); // Recrée le niveau.
    }
}

// Permet de vérifier si le joueur a gagné la partie.
void Map::checkWin() {
    if(this->myMario->getMario()->getPosX() >= winPosition && !winChecked){

        // Initialisation des composants de l'état "win".
        QPixmap * winpixmap = new QPixmap("..\\UnPiouMario\\images\\win.png");
        QGraphicsPixmapItem * pixwin = new QGraphicsPixmapItem(*winpixmap, nullptr);
        pixwin->setPos(scroll->value() + 143, 330);

        addItem(pixwin);

        this->soundManager->musique.stop();
        playSound("win"); // Musique de la victoire.
        winChecked = true;
    }
    if(winChecked){
        QList<Castle*> * listeCastleRight = (QList<Castle*>*)getGraphicsItem("castleR");
        Q_FOREACH(Castle * castle, *listeCastleRight){
            castle->setPos(castle->getPosX(), castle->getPosY());
            castelPosition = castle->getPosX(); // Récupération de la position du chateau de fin.
            addItem(castle);
        }
        // Déplace automatiquement le mario dans le chateau en fin de niveau.
        if(this->myMario->getMario()->getPosX() <= castelPosition) {
            this->myMario->getMario()->moveRight();
        }

        // Bloquage des événements du clavier.
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Up");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Up", false);
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Left");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Left", false);
        this->myMario->getMario()->getInputMap()->remove("Qt::Key_Right");
        this->myMario->getMario()->getInputMap()->insert("Qt::Key_Right", false);
    }
}

// Méthode permettant de jouer des bruitages et musiques.
void Map::playSound(QString sound){

    // Bruit des piques et son du game over.
    if(sound == "spikes" && !soundPlayed){
        this->soundManager->spikes.play();
        this->soundManager->gameover.play();
        this->soundManager->gameovermario.play();
        soundPlayed = true;
    }

    // Bruit de la chute dans un sol piégé.
    else if(sound == "soltrap" && !soundPlayed){
        this->soundManager->soltrap.play();
    }

    // Son de la victoire.
    else if(sound == "win" && !soundPlayed){
        this->soundManager->win.play();
        soundPlayed = true;
    }

    // Son de la défaite.
    else if(sound == "gameover" && !soundPlayed){
        this->soundManager->gameover.play();
        this->soundManager->gameovermario.play();
        soundPlayed = true;
    }

    // Bruitage d'une explosion et son du game over.
    else if(sound == "explosion" && !soundPlayed){
        this->soundManager->explosion.play();
        this->soundManager->gameover.play();
        this->soundManager->gameovermario.play();
        soundPlayed = true;
    }

    // Bruitage du bulltrap qui tue et son du game over.
    else if(sound == "bulltrap" && !soundPlayed){
        this->soundManager->bulltrap.play();
        this->soundManager->gameover.play();
        this->soundManager->gameovermario.play();
        soundPlayed = true;
    }

    // Bruitage du saut de mario.
    else if(sound == "jump" && !soundPlayed){
        int jumprandom = qrand()%3+1;
        switch(jumprandom){
            case 1:
            this->soundManager->jump.play();
                this->soundManager->jumpbis.play();
                break;
            case 2:
                this->soundManager->jump.play();
                this->soundManager->jumpter.play();
                break;
            case 3:
                this->soundManager->jump.play();
                this->soundManager->jumpqat.play();
                break;
        }
    }

    // Bruitage des collisions avec une brique.
    else if(sound == "bip" && !soundPlayed){
        this->soundManager->bip.play();
    }

    // Bruitage des bombes dans leur chute libre.
    else if(sound == "fallbomb" && !soundPlayed){
        this->soundManager->fallbomb.play();
    }
}

// Initialise le scroll au départ du niveau.
void Map::initScroll(){
    this->scroll->setValue(0);
}

void Map::setValueScroll(int value){
    this->scroll->setValue(value);
}
