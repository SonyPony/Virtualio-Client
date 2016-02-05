#include "timeoutanimation.h"

TimeoutAnimation::TimeoutAnimation(QQuickItem *parent): PaintedItem(parent)
{
    m_duration = 1000;
    m_widthAnimation = new QPropertyAnimation(this, "width", this);
    m_widthAnimation->setStartValue(0);

    connect(this, &TimeoutAnimation::durationChanged, m_widthAnimation, &QPropertyAnimation::setDuration);
    connect(m_widthAnimation, &QPropertyAnimation::finished, this, &TimeoutAnimation::timeout);
}

void TimeoutAnimation::paint(QPainter *painter)
{
    painter->setPen(m_color);
    painter->setBrush(m_color);
    painter->drawRect(this->boundingRect());
}

int TimeoutAnimation::duration() const
{
    return m_duration;
}

void TimeoutAnimation::start()
{
    m_widthAnimation->setEndValue(this->width());
    m_widthAnimation->start();
}

void TimeoutAnimation::resetAnimation()
{
    disconnect(m_widthAnimation, &QPropertyAnimation::finished, this, &TimeoutAnimation::timeout);
    m_widthAnimation->setCurrentTime(m_widthAnimation->duration());
    connect(m_widthAnimation, &QPropertyAnimation::finished, this, &TimeoutAnimation::timeout);
}

void TimeoutAnimation::setDuration(int duration)
{
    if (m_duration == duration)
        return;

    m_duration = duration;
    emit durationChanged(duration);
}

