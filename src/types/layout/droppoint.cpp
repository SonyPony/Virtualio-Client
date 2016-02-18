#include "droppoint.h"

DropPoint::DropPoint(QQuickItem *parent): PaintedItem(parent), m_taken(false)
{
}

void DropPoint::paint(QPainter *painter)
{
    painter->setPen(QPen("transparent"));
    painter->setBrush(QBrush(m_color));
    painter->drawRect(boundingRect());
}

bool DropPoint::taken() const
{
    return m_taken;
}

void DropPoint::setTaken(bool taken)
{
    if (m_taken == taken)
        return;

    m_taken = taken;
    emit takenChanged(taken);
}


