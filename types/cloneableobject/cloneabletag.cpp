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

void CloneableTag::mousePressEvent(QMouseEvent *)
{
    QPointer<CloneTag> instance = m_manager->clone(this);
    m_dropGrid->registerObject(instance);
    instance->grabMouse();
}

DropGrid *CloneableTag::dropGrid() const
{
    return m_dropGrid;
}

void CloneableTag::setDropGrid(DropGrid *dropGrid)
{
    if (m_dropGrid == dropGrid)
        return;

    m_dropGrid = dropGrid;
    emit dropGridChanged(dropGrid);
}

