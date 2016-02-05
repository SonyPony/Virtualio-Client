#include "tab.h"

Tab::Tab(QQuickItem *parent): QQuickItem(parent)
{
    m_moveAnimation = new MoveAnimation(this, 400, this);
    m_moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_index = -1;
    setClip(true);

    connect(m_moveAnimation, &MoveAnimation::finished, [this]() {
        if(m_moveAnimation->endValue() == QPointF(0, 0))
            Q_EMIT this->showed();
        else
            Q_EMIT this->hided();
    });
}

int Tab::index() const
{
    return m_index;
}

void Tab::setIndex(int index)
{
    if (m_index == index)
        return;

    m_index = index;
    emit indexChanged(index);
}

void Tab::move(QPointF destination)
{
    m_moveAnimation->setStartValue(position());
    m_moveAnimation->setEndValue(destination);

    m_moveAnimation->start();
}
