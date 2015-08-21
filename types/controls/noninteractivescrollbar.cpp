#include "noninteractivescrollbar.h"
#include <QPropertyAnimation>

NonInteractiveScrollBar::NonInteractiveScrollBar(): m_active(false), m_orientation(Qt::Vertical)
{
    m_resizeAnimation = new QPropertyAnimation(this);
    m_resizeAnimation->setTargetObject(this);

    m_resizeAnimation->setDuration(300);
    m_resizeAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
}

void NonInteractiveScrollBar::paint(QPainter *painter)
{
    painter->setBrush(QBrush(m_color));
    painter->setPen(QPen(m_color));
    painter->drawRect(boundingRect());
}

QColor NonInteractiveScrollBar::color() const
{
    return m_color;
}

int NonInteractiveScrollBar::orientation() const
{
    return m_orientation;
}

int NonInteractiveScrollBar::position() const
{
    return m_position;
}

bool NonInteractiveScrollBar::active() const
{
    return m_active;
}

void NonInteractiveScrollBar::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

void NonInteractiveScrollBar::setOrientation(int orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    emit orientationChanged(orientation);
}

void NonInteractiveScrollBar::setPosition(qreal position)
{
    if (m_position == position)
        return;

    m_position = position;

    if(m_orientation == Qt::Horizontal)
        setX(position);
    else if(m_orientation == Qt::Vertical)
        setY(position);

    emit positionChanged(position);
}

void NonInteractiveScrollBar::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active = active;

    const QString strTargetProperty = (m_orientation == Qt::Horizontal) ?"height" :"width";
    const double targetProperty = (strTargetProperty == "width") ?width() :height();
    const double sizeMultiplicator = 1;

    m_resizeAnimation->setPropertyName(strTargetProperty.toLocal8Bit());
    m_resizeAnimation->setStartValue(targetProperty);
    //For example sizemul = 2 -> active * 3/2 + 1/2 make twice bigger if active else twice smaller
    m_resizeAnimation->setEndValue(targetProperty * ((double)m_active * (sizeMultiplicator - 1. / sizeMultiplicator) + 1. / sizeMultiplicator));

    m_resizeAnimation->start();

    emit activeChanged(active);
}

