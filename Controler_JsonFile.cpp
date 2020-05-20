#include "Controler_JsonFile.h"

#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>


/**
 * @brief Controler_JsonFile::readJson : lis toutes les données du jeu
 * @return
 */
QJsonObject Controler_JsonFile::readJson()
{
    QString val;
    QFile file;
    file.setFileName("..\\Json\\test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

    QJsonObject sett2 = d.object();

    return sett2;
}

/**
 * @brief Controler_JsonFile::getMario
 * récupere l'image de mario
 * @param all : objet contenant toutes les donnees du jeu
 * @return
 */
QJsonObject Controler_JsonFile::getMario(QJsonObject all)
{
    return all["mario"].toObject();
}

/**
 * @brief Controler_JsonFile::getMap
 * recupere le JsonObject correspondant a la map
 * @param all
 * @return
 */
QJsonObject Controler_JsonFile::getMap(QJsonObject all)
{
    return all["map"].toObject();
}

QJsonObject Controler_JsonFile::getPieges(QJsonObject all)
{
    return all["pieges"].toObject();
}
