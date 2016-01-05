#include "moveanimation.h"
#include <QDebug>

MoveAnimation::MoveAnimation(QObject *parent) : QObject(parent)
{
    m_xAnimation = new QPropertyAnimation(this);
    m_yAnimation = new QPropertyAnimation(this);

    m_moveAnimation = new QParallelAnimationGroup(this);
    m_moveAnimation->addAnimation(m_xAnimation);
    m_moveAnimation->addAnimation(m_yAnimation);

    connect(m_moveAnimation, &QParallelAnimationGroup::finished, this, &MoveAnimation::finished);
}

MoveAnimation::MoveAnimation(QObject *target, int duration, QObject *parent): QObject(parent)
{
    m_xAnimation = new QPropertyAnimation(target, "x", this);
    m_yAnimation = new QPropertyAnimation(target, "y", this);
    m_xAnimation->setDuration(duration);
    m_yAnimation->setDuration(m_xAnimation->duration());

    m_moveAnimation = new QParallelAnimationGroup(this);
    m_moveAnimation->addAnimation(m_xAnimation);
    m_moveAnimation->addAnimation(m_yAnimation);

    connect(m_moveAnimation, &QParallelAnimationGroup::finished, this, &MoveAnimation::finished);
}

int MoveAnimation::duration() const
{
    return m_duration;
}

QObject *MoveAnimation::target() const
{
    return m_target;
}

QEasingCurve MoveAnimation::easingCurve() const
{
    return m_easingCurve;
}

QPointF MoveAnimation::startValue() const
{
    return m_startValue;
}

QPointF MoveAnimation::endValue() const
{
    return m_endValue;
}

void MoveAnimation::start()
{
    m_moveAnimation->start();
}

void MoveAnimation::stop()
{
    m_moveAnimation->stop();
}

void MoveAnimation::resume()
{
    m_moveAnimation->resume();
}

void MoveAnimation::pause()
{
    m_moveAnimation->pause();
}

void MoveAnimation::setDuration(int duration)
{
    m_duration = duration;
    m_xAnimation->setDuration(m_duration);
    m_yAnimation->setDuration(m_duration);
    emit durationChanged(duration);
}

void MoveAnimation::setTarget(QObject *target)
{
    if (m_target == target)
        return;

    m_target = target;
    m_xAnimation->setTargetObject(target);
    m_yAnimation->setTargetObject(target);
    emit targetChanged(target);
}
;
void MoveAnimation::setEasingCurve(QEasingCurve easingCurve)
{
    if (m_easingCurve == easingCurve)
        return;

    m_easingCurve = easingCurve;
    m_xAnimation->setEasingCurve(m_easingCurve);
    m_yAnimation->setEasingCurve(m_easingCurve);
    emit easingCurveChanged(easingCurve);
}

void MoveAnimation::setStartValue(QPointF startValue)
{
    m_startValue = startValue;
    m_xAnimation->setStartValue(m_startValue.x());
    m_yAnimation->setStartValue(m_startValue.y());
    emit startValueChanged(startValue);
}

void MoveAnimation::setEndValue(QPointF endValue)
{
    m_endValue = endValue;
    m_xAnimation->setEndValue(m_endValue.x());
    m_yAnimation->setEndValue(m_endValue.y());
    emit endValueChanged(endValue);
}
