#include "cloneabletag.h"

CloneableTag::CloneableTag()
{
    m_manager = new CloneManager(this);
    m_tagAppearance = new TagAppearance(QColor("#E6063C"), QColor("#C40002"), this);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void CloneableTag::paint(QPainter *painter)
{
    painter->setBrush(QBrush("blue"));
    //painter->drawRect(boundingRect());

    m_tagAppearance->paintTag(painter);
}

void CloneableTag::mousePressEvent(QMouseEvent *)
{
    QPointer<CloneTag> instance = m_manager->clone(m_tagAppearance, this);
    instance->grabMouse();
    emit newObject(instance);
}

