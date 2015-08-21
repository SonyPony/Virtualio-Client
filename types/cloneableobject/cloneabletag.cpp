#include "cloneabletag.h"

CloneableTag::CloneableTag()
{
    m_manager = new CloneManager;
    setAcceptedMouseButtons(Qt::AllButtons);
}

void CloneableTag::paint(QPainter *painter)
{
    painter->setBrush(QBrush("blue"));
    painter->drawRect(boundingRect());
}

void CloneableTag::mousePressEvent(QMouseEvent *event)
{
    QPointer<CloneTag> instance = m_manager->clone(this);
    instance->grabMouse();
}

