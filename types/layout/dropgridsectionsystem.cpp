#include "dropgridsectionsystem.h"
#include <QDebug>
#include <stdexcept>

QPoint DropGridSectionSystem::sectionPos(int index, QSize matrixSize)
{
    if(index >= matrixSize.width() * matrixSize.height())
        throw std::range_error("Index out of range of matrix.");
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
        throw std::range_error("Point dropped out of grid.");

    //calculate matrix position
    QPoint matrixPosition;
    matrixPosition.rx() = floor((droppedPoint.x() - gridSize.x()) / gridSize.width() * (double)matrixSize.width());
    matrixPosition.ry() = floor((droppedPoint.y() - gridSize.y()) / gridSize.height() * (double)matrixSize.height());

    return matrixSize.width() * matrixPosition.y() + matrixPosition.x();
}


int DropGridSectionSystem::neighborSectionIndex(int currentSectionIndex, Qt::WindowFrameSection neighborSide, QSize matrixSize)
{
    if(neighborSide != Qt::TopSection && neighborSide != Qt::BottomSection && neighborSide != Qt::LeftSection && neighborSide != Qt::RightSection)
        throw std::invalid_argument("Invalid neighbor side.");

    QPoint sectionPos = DropGridSectionSystem::sectionPos(currentSectionIndex, matrixSize);
    QPoint neighborPos;

    if(neighborSide == Qt::TopSection)
        neighborPos = sectionPos - QPoint(0, 1);
    else if(neighborSide == Qt::BottomSection)
        neighborPos = sectionPos + QPoint(0, 1);
    else if(neighborSide == Qt::LeftSection)
        neighborPos = sectionPos - QPoint(1, 0);
    else if(neighborSide == Qt::RightSection)
        neighborPos = sectionPos + QPoint(1, 0);

    return DropGridSectionSystem::sectionIndex(neighborPos, matrixSize);
}

int DropGridSectionSystem::sectionIndex(QPoint sectionPos, QSize matrixSize)
{
    if(sectionPos.x() < 0 || sectionPos.y() < 0 || sectionPos.x() > matrixSize.width() - 1 || sectionPos.y() > matrixSize.height() - 1)
        throw std::range_error("Section position is out of matrix");

    return matrixSize.width() * sectionPos.y() + sectionPos.x();
}

QList<int> DropGridSectionSystem::dropPointsInRow(int dropPointIndex, QSize matrixSize)
{
    if(dropPointIndex >= (matrixSize.width() - 1) * (matrixSize.height() - 1))
        throw std::range_error("Index out of range of matrix.");
    QList<int> result;
    int dropPointsRow = floor((double)dropPointIndex / (matrixSize.width() - 1));
    int rowStartIndex = dropPointsRow * (matrixSize.width() - 1);
    int rowEndIndex = rowStartIndex + matrixSize.width() - 2;

    for(int i = rowStartIndex; i <= rowEndIndex; i++)
        result.append(i);
    return result;
}


QPoint DropGridSectionSystem::dropPointMatrixPos(int dropPointIndex, QSize matrixSize)
{
    if(dropPointIndex >= (matrixSize.width() - 1) * (matrixSize.height() - 1))
        throw std::range_error("Index out of range of matrix.");
    return QPoint(
                dropPointIndex % (matrixSize.width() - 1),
                dropPointIndex / (matrixSize.width() - 1)
                );
}
