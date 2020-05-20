#include "Controler_moteur.h"
#include "Controler_JsonFile.h"

#include <QDirIterator>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>


Moteur::Moteur()
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
}



/*Méthode pour charger tous les éléments du jeu*/
void Moteur::loadingGame()
{

    //lecture des données de jeu
    QJsonObject all_data = Controler_JsonFile::readJson();

    //on parkouuuuuuuuuuuuuur tous les objets présent dans les données du jeu










    //on charge une image
    QGraphicsPixmapItem item;
    QImage image;

    //creation d'un iterateur pour parcourir tous les folders
    QDirIterator it("E:/QT_Projects/MoteurV1/image", QStringList() << "*", QDir::NoDotAndDotDot | QDir::AllDirs, QDirIterator::Subdirectories);

    qDebug() << QDir::currentPath();
    while (it.hasNext()) {

        QFile f(it.next());
        f.open(QIODevice::ReadOnly);

        QDir imageDirectory(f.fileName());
        QStringList images = imageDirectory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);

        foreach(QString filename, images)
        {
            //switch pour choisir quel type d'objet créé

            //on mets l'image dans l'objet

            //ajout de l'objet dans la liste des objets

            //ajout de l'objet dans la vue

            QImage image(f.fileName()+"/"+filename);

            QGraphicsPixmapItem *i = new QGraphicsPixmapItem(QPixmap::fromImage(image));

            scene->addItem(i);
        }
    }
}
