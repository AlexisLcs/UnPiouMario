#ifndef LABEL_H
#define LABEL_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class ScreenLabel : public QGraphicsTextItem
{
public:
    ScreenLabel(QGraphicsTextItem *parent = 0);
};

#endif // FLAG_H
