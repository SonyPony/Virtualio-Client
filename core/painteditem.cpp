#include "painteditem.h"

PaintedItem::PaintedItem(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

QColor PaintedItem::color() const
{
    return m_color;
}

void PaintedItem::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

