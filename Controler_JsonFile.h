#ifndef CONTROLER_JSONFILE_H
#define CONTROLER_JSONFILE_H

#include <QJsonObject>



class Controler_JsonFile
{
public:

    static QJsonObject readJson();

    //methodes pour recuperer un type d'objets
    static QJsonObject getMario(QJsonObject all);
    static QJsonObject getMap(QJsonObject all);
    static QJsonObject getPieges(QJsonObject all);


};

#endif // CONTROLER_JSONFILE_H
