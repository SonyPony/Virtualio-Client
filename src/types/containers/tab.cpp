#include "tab.h"

Tab::Tab(QQuickItem *parent): QQuickItem(parent)
{
    m_moveAnimation = new MoveAnimation(this, 400, this);
    m_moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_index = -1;
    setClip(true);
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
