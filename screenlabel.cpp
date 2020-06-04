#include "screenlabel.h"

ScreenLabel::ScreenLabel(QGraphicsTextItem *parent)
    :QGraphicsTextItem(parent)
{
    setFlag(ItemClipsToShape);
}
