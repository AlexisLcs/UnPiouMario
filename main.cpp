#include <QApplication>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QScreen>
#include <QIcon>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopWidget>
#include <QSplashScreen>

#include "brick.h"
#include "map.h"

//méthode pour centrer la fenetre par rapport à l'ecran
void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget * desktop = QApplication::desktop();

    //récupération de la résolution de l'écran
    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - Map::Longueur) / 2;
    y = (screenHeight - Map::Hauteur) / 2;

    // on redimensionne la fenetre
    widget.setGeometry(x, y, Map::Longueur, Map::Hauteur);
    // on la centre
    widget.move(qApp->screens()[0]->size().width() / 2 - (Map::Longueur / 2),qApp->screens()[0]->size().height() / 2 - (Map::Hauteur / 2));
    widget.setFixedSize(Map::Longueur, Map::Hauteur); //taille fixe (pas redimensionnable)
}

//methode de lecture du fichier map.json
QJsonObject readJson()
{
    QString val;
    QFile file;
    file.setFileName("..\\UnPiouMario\\map.json"); // récupération du chemin
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll(); //lecture
    file.close();

    //conversion en QJsonObject
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8()); //encodage du retour de lecture afin de formater le fichier correctement
    QJsonObject sett2 = d.object(); //conversion en QJsonObject

    return sett2;
}

//todo lucas
int main(int argc, char *argv[])
{
    //creation de la vue
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("..\\UnPiouMario\\images\\unpiou"));

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("..\\UnPiouMario\\images\\title.png"));


    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsView view(scene);
    view.setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    //lecture du json
    QJsonObject listeAll = readJson();

    //creation du scroll
    QScrollBar * scroll = new QScrollBar();
    scroll = view.horizontalScrollBar();

    //creation de la map (contenu de la vue)
    Map * scenemap = new Map(scroll, listeAll, scene);

    view.setScene(scenemap); //notre map devient notre scene
    view.setBackgroundBrush(QColor(111, 135, 249)); //on definit la couleur du background
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //desactivation du scroll manuel
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scenemap->initScroll(); //initialisation du scroll
    view.setWindowTitle("UnPiouMario !"); //titre de la fenetre

    splash->show();

    QTimer::singleShot(2000,splash,SLOT(close()));

    QTimer::singleShot(2000,&view,SLOT(show()));
    QTimer::singleShot(2010,scenemap,SLOT(initScroll()));
    //affichage
    //view.show();

    center(view);

    return a.exec();
}
