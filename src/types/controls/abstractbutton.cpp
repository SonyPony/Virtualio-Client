#include "abstractbutton.h"

void AbstractButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_pressed = true;
}

void AbstractButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(boundingRect().contains(event->pos()) && m_pressed)
        emit clicked(event->pos());
    m_pressed = false;
}

void AbstractButton::hoverEnterEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;

    Q_EMIT entered();
}

void AbstractButton::hoverLeaveEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;

    Q_EMIT leaved();
}

AbstractButton::AbstractButton(QQuickItem *parent): PaintedItem(parent)
{
    m_pressed = false;
    m_hovered = false;

    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

