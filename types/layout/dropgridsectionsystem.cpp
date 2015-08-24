#include "dropgridsectionsystem.h"
#include <QDebug>
#include <stdexcept>

QPoint DropGridSectionSystem::sectionPos(int index, QSize matrixSize)
{
    if(index >= matrixSize.width() * matrixSize.height())
        throw std::out_of_range("Index out of range of matrix.");
    return QPoint(
                index % matrixSize.width(),
                index / matrixSize.width()
                );
}

QList<int> DropGridSectionSystem::dropPointIndexes(int index, QSize matrixSize)
{
    QList<int> dropPointIndexes;
    QPoint sectionPos = DropGridSectionSystem::sectionPos(index, matrixSize);

    //has top left drop point
    if(sectionPos.x() > 0 && sectionPos.y() > 0)
        dropPointIndexes.append(
            (matrixSize.width() - 1) * (sectionPos.y() - 1) + sectionPos.x() - 1
        );
    //has bottom left drop point
    if(sectionPos.x() > 0 && sectionPos.y() < matrixSize.height() - 1)
        dropPointIndexes.append(
            (matrixSize.width() - 1) * (sectionPos.y() - 1) + sectionPos.x() + matrixSize.width() - 2
        );
    //has top right drop point
    if(sectionPos.x() < matrixSize.width() - 1 &&  sectionPos.y() > 0)
        dropPointIndexes.append(
            (matrixSize.width() - 1) * (sectionPos.y() - 1) + sectionPos.x()
        );
    //has bottom right drop point
    if(sectionPos.x() < matrixSize.width() - 1 &&  sectionPos.y() < matrixSize.height() - 1)
        dropPointIndexes.append(
            (matrixSize.width() - 1) * (sectionPos.y() - 1) + sectionPos.x() + matrixSize.width() - 1
        );

    return dropPointIndexes;
}

int DropGridSectionSystem::sectionIndex(QPointF droppedPoint, QSize matrixSize, QRectF gridSize)
{
    //check out of range
    if( droppedPoint.x() < gridSize.x() || droppedPoint.y() < gridSize.y() ||
        droppedPoint.x() > gridSize.x() + gridSize.width() - 1 || droppedPoint.y() > gridSize.y() + gridSize.height() - 1)
        throw std::out_of_range("Point dropped out of grid.");

    //calculate matrix position
    QPoint matrixPosition;
    matrixPosition.rx() = floor((droppedPoint.x() - gridSize.x()) / gridSize.width() * (double)matrixSize.width());
    matrixPosition.ry() = floor((droppedPoint.y() - gridSize.y()) / gridSize.height() * (double)matrixSize.height());

    return matrixSize.width() * matrixPosition.y() + matrixPosition.x();
}

