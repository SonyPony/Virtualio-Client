#include "tagpinview.h"

TagPinView::TagPinView(QQuickItem *parent): QQuickPaintedItem(parent)
{
    m_pinNumber = "N";
    setParentItem(parent);
}

void TagPinView::paintPinView(QPainter *painter)
{
    QRectF componentRect(x(), y(), width(), height());

    painter->setPen(QPen(m_color));
    painter->setBrush(QBrush(m_color));

    painter->drawRect(componentRect);

    painter->setPen(QPen(m_textColor));
    painter->drawText(componentRect, m_pinNumber, QTextOption(Qt::AlignCenter));
}

QColor TagPinView::color() const
{
    return m_color;
}

QColor TagPinView::textColor() const
{
    return m_textColor;
}

void TagPinView::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

void TagPinView::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void TagPinView::setPinNumber(int pin)
{
    if(pin == m_pinNumber.toInt())
        return;

    if(pin == -1)
        m_pinNumber = "N";

    else
        m_pinNumber = QString::number(pin);

    parentItem()->update();
}

