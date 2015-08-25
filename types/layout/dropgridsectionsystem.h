#ifndef DROPGRIDSECTION_H
#define DROPGRIDSECTION_H

#include <QList>
#include <QPoint>
#include <QSize>
#include <QRectF>

namespace DropGridSectionSystem
{
    QPoint sectionPos(int index, QSize matrixSize);
    QList<int> dropPointIndexes(int index, QSize matrixSize);
    int sectionIndex(QPointF droppedPoint, QSize matrixSize, QRectF gridSize);
    int sectionIndex(QPoint sectionPos, QSize matrixSize);
    int neighborSectionIndex(int currentSectionIndex, int neighborSide, QSize matrixSize);
}

#endif // DROPGRIDSECTIONSYSTEM_H
