#include <QApplication>
#include <QDir>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QScreen>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopWidget>

#include "brick.h"
#include "map.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget * desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - Map::Longueur) / 2;
    y = (screenHeight - Map::Hauteur) / 2;

    widget.setGeometry(x, y, Map::Longueur, Map::Hauteur);
    widget.move(qApp->screens()[0]->size().width() / 2 - (Map::Longueur / 2),qApp->screens()[0]->size().height() / 2 - (Map::Hauteur / 2));
    widget.setFixedSize(Map::Longueur, Map::Hauteur);
}

QJsonObject readJson()
{
    QString val;
    QFile file;
    file.setFileName("..\\UnPiouMario\\map.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject sett2 = d.object();

    return sett2;
}

QJsonObject getBricks(QJsonObject all)
{
    return all["bricks"].toObject();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsView view(scene);
    view.setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    QJsonObject listeAll = readJson();

    QScrollBar * scroll = new QScrollBar();
    scroll = view.horizontalScrollBar();

    Map * scenemap = new Map(scroll, listeAll, scene);

    view.setScene(scenemap);
    view.setBackgroundBrush(QColor(111, 135, 249));
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.setWindowTitle("Maiiiiiiiiiiiiiiiiiiiis QUOIIIIIIIIIIIIIIIIIIIIIII !");
    view.show();
    scenemap->initScroll();

    center(view);

    //qDebug() << "App path : " << qApp->applicationDirPath();
    return a.exec();
}
