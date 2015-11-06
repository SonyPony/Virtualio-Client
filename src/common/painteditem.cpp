#include "painteditem.h"

PaintedItem::PaintedItem(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

QColor PaintedItem::color() const
{
    return m_color;
}

QPoint PaintedItem::pos() const
{
    return QPoint(x(), y());
}

QRect PaintedItem::rect() const
{
    return QRect(x(), y(), width(), height());
}

void PaintedItem::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

