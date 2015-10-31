#include "dropgridsmanager.h"

DropGridsManager::DropGridsManager(QObject *parent) : QObject(parent)
{
    m_objectsParent = 0;
}

void DropGridsManager::setObjectsParent(QQuickItem *parent)
{
    m_objectsParent = parent;
}

void DropGridsManager::registerObject(DropableObject *object)
{
    object->setParentItem(m_objectsParent);
    for(DropGrid* grid: m_dropGrids)
        grid->registerObject(object);
}

QList<DropGrid *> DropGridsManager::dropGrids() const
{
    return m_dropGrids;
}

void DropGridsManager::unregisterObject(DropableObject *object)
{
    for(DropGrid* grid: m_dropGrids)
        grid->unregisterObjectFromMatrix(object);
    emit object->deleteRequest();
}

void DropGridsManager::unblockDropGridSignal()
{
    for(DropGrid* grid: m_dropGrids)
        connect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::registerGrid(DropGrid *grid)
{
    m_dropGrids.append(grid);
    connect(grid, SIGNAL(objectMoved(DropableObject*)), this, SLOT(checkObjectMove(DropableObject*)));
    connect(grid, SIGNAL(rowIsFull(DropableObject*)), this, SLOT(unregisterObject(DropableObject*)));
    connect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::unregisterGrid(DropGrid *grid)
{
    m_dropGrids.removeOne(grid);
    disconnect(grid, SIGNAL(objectMoved(DropableObject*)), this, SLOT(checkObjectMove(DropableObject*)));
    disconnect(grid, SIGNAL(rowIsFull(DropableObject*)), this, SLOT(unregisterObject(DropableObject*)));
    disconnect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::checkObjectDrop(DropableObject *object)
{
    bool isInsideOfSomeGrid = false;

    for(DropGrid* grid: m_dropGrids) {
        if(grid->objectInsideGrid(object))
            isInsideOfSomeGrid = true;
    }

    if(!isInsideOfSomeGrid) {
        for(DropGrid* grid: m_dropGrids) {
            //need to check here because of blocking multiple handling same signal
            grid->checkDropPointRelease(object);
            //grid->unregisterObject(object);
            disconnect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
        }

        connect(object, SIGNAL(destroyed(QObject*)), this, SLOT(unblockDropGridSignal()));
        unregisterObject(object);
    }
}

void DropGridsManager::checkObjectMove(DropableObject *object)
{
    bool objectIsInSomeGrid = false;

    for(DropGrid* grid: m_dropGrids) {
        if(grid->objectInsideGrid(object)) {
            objectIsInSomeGrid = true;
            object->setMatrixPosition(grid->getObjectActualMatrixPos(object));
        }
    }

    if(objectIsInSomeGrid)
        object->enteredIntoGrid();

    else {
        object->leavedFromGrid();
        object->setMatrixPosition(QPoint(-1, -1));
    }
}

