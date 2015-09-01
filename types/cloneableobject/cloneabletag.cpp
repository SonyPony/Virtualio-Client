#include "cloneabletag.h"

CloneableTag::CloneableTag()
{
    m_dropGridManager = new DropGridsManager;
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

    foreach (DropGrid* grid, m_dropGridManager->dropGrids()) {
        grid->registerObject(instance);
    }
    instance->grabMouse();
}

void CloneableTag::registerDropGrid(DropGrid *grid)
{
    m_dropGridManager->registerGrid(grid);
}

void CloneableTag::unregisterDropGrid(DropGrid *grid)
{
    m_dropGridManager->unregisterGrid(grid);
}

