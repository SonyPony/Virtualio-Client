#include "droppoint.h"

DropPoint::DropPoint(QQuickItem *parent): PaintedItem(parent)
{
}

void DropPoint::paint(QPainter *painter)
{
    painter->setBrush(QBrush("orange"));
    painter->drawRect(boundingRect());
}

