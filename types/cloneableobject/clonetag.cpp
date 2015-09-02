#include "clonetag.h"

/*CloneTag::CloneTag()
{
    setWidth(100);
    setHeight(100);
    update(QRect(0, 0, 100, 100));
}*/

CloneTag::CloneTag(int index, QObject *parent): CloneObject(index, parent)
{
    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_opacityAnimation->setDuration(150);

    setFlag(QQuickItem::ItemAcceptsDrops);
    setAcceptedMouseButtons(Qt::AllButtons);
    setWidth(50);
    setHeight(18);
    update(boundingRect().toRect());

}

void CloneTag::paint(QPainter *painter)
{
    painter->setPen(QPen("transparent"));
    painter->setBrush(QBrush("red"));
    painter->drawRect(boundingRect());
}

void CloneTag::enteredIntoGrid()
{
    if(m_opacityAnimation->Running)
        m_opacityAnimation->stop();

    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->start();
}

void CloneTag::leavedFromGrid()
{
    if(m_opacityAnimation->Running)
        m_opacityAnimation->stop();

    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(0.5);
    m_opacityAnimation->start();
}

