#include "dropgridsmanager.h"

DropGridsManager::DropGridsManager(QObject *parent) : QObject(parent)
{

}

QList<DropGrid *> DropGridsManager::dropGrids() const
{
    return m_dropGrids;
}

void DropGridsManager::unregisterObject(DropableObject *object)
{
    foreach(DropGrid* grid, m_dropGrids)
        grid->unregisterObjectFromMatrix(object);
    emit object->deleteRequest();
}

void DropGridsManager::unblockDropGridSignal()
{
    foreach(DropGrid* grid, m_dropGrids)
        connect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::registerGrid(DropGrid *grid)
{
    m_dropGrids.append(grid);
    connect(grid, SIGNAL(rowIsFull(DropableObject*)), this, SLOT(unregisterObject(DropableObject*)));
    connect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::unregisterGrid(DropGrid *grid)
{
    m_dropGrids.removeOne(grid);
    disconnect(grid, SIGNAL(rowIsFull(DropableObject*)), this, SLOT(unregisterObject(DropableObject*)));
    disconnect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
}

void DropGridsManager::checkObjectDrop(DropableObject *object)
{
    bool isInsideOfSomeGrid = false;

    foreach(DropGrid* grid, m_dropGrids) {
        if(grid->objectInsideGrid(object))
            isInsideOfSomeGrid = true;
    }

    if(!isInsideOfSomeGrid) {
        foreach(DropGrid* grid, m_dropGrids) {
            //need to check here because of blocking multiple handling same signal
            grid->checkDropPointRelease(object);
            grid->unregisterObject(object);
            disconnect(grid, SIGNAL(droppedOutOfGrid(DropableObject*)), this, SLOT(checkObjectDrop(DropableObject*)));
        }

        connect(object, SIGNAL(destroyed(QObject*)), this, SLOT(unblockDropGridSignal()));
        unregisterObject(object);
    }
}

