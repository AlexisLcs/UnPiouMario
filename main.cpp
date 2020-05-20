#include "Controler_moteur.h"
#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    view w;

    /*ouverture et chargement des fichiers*/
    Moteur moteur = Moteur();
    moteur.loadingGame();

    w.show();
    return a.exec();
}
