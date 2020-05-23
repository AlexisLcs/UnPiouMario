#ifndef MODEL_PIEGE_H
#define MODEL_PIEGE_H

#include <QImage>


class Piege
{
private:

    //attributs
    QImage image; //image du piege

public:
    Piege();


    QImage getImage() const;
    void setImage(const QImage &value);
};

#endif // MODEL_PIEGE_H
