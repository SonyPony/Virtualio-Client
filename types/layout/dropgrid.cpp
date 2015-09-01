#include "dropgrid.h"
#include "dropgridsectionsystem.h"
#include "../../core/extentedmath.h"
#include "../../core/graphicallogic.h"
#include <stdexcept>
#include <algorithm>
#include "../../core/interval.h"
#include <QPair>

DropGrid::DropGrid()
{
    m_matrixSize = QSize(0, 0);

    connect(this, SIGNAL(dropPointReleased(int)), this, SLOT(shiftObjectsCurrentDropPoint(int)));
    connect(this, SIGNAL(columnsChanged(int)), this, SLOT(reinitDropPoints()));
    connect(this, SIGNAL(rowsChanged(int)), this, SLOT(reinitDropPoints()));
}

DropGrid::~DropGrid()
{
    foreach (QPointer<DropPoint> value, m_dropPoints)
        value->deleteLater();
}

void DropGrid::paint(QPainter *painter)
{
    if(!m_dropPoints.size())    //there is not any DropPoint
        return;

    const double pieceHor = width() / (double)(m_columns);
    const double pieceVer = height() / (double)(m_rows);

    //move to reinit
    foreach (QPointer<DropPoint> dropPoint, m_dropPoints) {
        int i = m_dropPoints.indexOf(dropPoint);
        QPointF dropPointCenter = GraphicalLogic::relativeCenterPoint(dropPoint);

        dropPoint->setX(pieceHor * (double)(i % (m_columns - 1) + 1.) - dropPointCenter.x());
        dropPoint->setY(pieceVer * floor(i / (m_columns - 1) + 1.) - dropPointCenter.y());
    }

    //painter->setPen(QPen("red"));
    //painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));

}

bool DropGrid::objectInsideGrid(DropableObject *object)
{
    bool res = ExtentedMath::pointInRect(GraphicalLogic::centerPoint(object).toPoint(), QRect(position().toPoint(), QSize(width(), height())));
    return res;
}

void DropGrid::registerObject(DropableObject *object)
{
    connect(object, SIGNAL(dropped(DropableObject*)), this, SLOT(handleObjectDrop(DropableObject*)));
}

void DropGrid::unregisterObject(DropableObject *object)
{
    disconnect(object, SIGNAL(dropped(DropableObject*)), this, SLOT(handleObjectDrop(DropableObject*)));
}

int DropGrid::rows() const
{
    return m_rows;
}

int DropGrid::columns() const
{
    return m_columns;
}

int DropGrid::objectsAlign() const
{
    return m_objectsAlign;
}

void DropGrid::reinitDropPoints()
{
    Interval validRange(0, 40);

    if(!validRange.isIn(m_columns) || !validRange.isIn(m_rows))
        return;

    QList<QPointer<DropPoint> > toDelete;
    if(m_dropPoints.size() > (m_columns - 1) * (m_rows - 1) && m_columns && m_rows) {
        for(int i = (m_columns - 1) * (m_rows - 1); i < m_dropPoints.size(); i++)
            toDelete.append(m_dropPoints.at(i));
        foreach (QPointer<DropPoint> item, toDelete) {
            m_dropPoints.removeOne(item);
            item->deleteLater();
        }
    }

    else {
        for(int i = m_dropPoints.size(); i < (m_columns - 1) * (m_rows - 1); i++) {
            m_dropPoints.append(new DropPoint(this));
            m_dropPoints[i]->setWidth(3);
            m_dropPoints[i]->setHeight(3);
        }
    }

    update();
}

void DropGrid::handleObjectDrop(DropableObject *object)
{
    try {
        const int sectionIndex = DropGridSectionSystem::sectionIndex(
                                     GraphicalLogic::centerPoint(object),
                                     m_matrixSize,
                                     QRectF(x(), y(), width(), height())
                                 );
        const QList<int> dropPointIndexes = DropGridSectionSystem::dropPointIndexes(sectionIndex, m_matrixSize);
        //fixing relative positioning calculation
        QPointF gridPos = this->position();
        QPair<int, double> closestPoint = qMakePair(-1, INT16_MAX);
        const int objectKeyInMatrix = m_matrix.key(object, -1);

        foreach (int i, dropPointIndexes) {
            double distance =  ExtentedMath::distance(
                                   GraphicalLogic::centerPoint(gridPos + m_dropPoints[i]->position(), m_dropPoints[i]->boundingRect().size()) ,
                                   GraphicalLogic::centerPoint(object));

            if(distance < closestPoint.second) {
                closestPoint.first = i;
                closestPoint.second = distance;
            }
        }

        const int availableDropPointIndex = findAvailableDropPoint(m_dropPoints[closestPoint.first], m_objectsAlign);
        //get list of indexes of drop points in row and search if closest point index is in the same list as previous drop point
        const bool objectDroppedInSameRow = DropGridSectionSystem::dropPointsInRow(
                                          closestPoint.first,
                                          m_matrixSize).indexOf(objectKeyInMatrix) > -1;
        const bool objectNeverHaveBeenAligned = !(objectKeyInMatrix + 1);

        if(objectNeverHaveBeenAligned || !objectDroppedInSameRow) {    //newly inited objects and objects dropped from an another row
            if(!objectNeverHaveBeenAligned) {   //if object was dropped from another row
                int dropPointIndex = objectKeyInMatrix;
                unregisterObjectFromMatrix(object);

                emit dropPointReleased(dropPointIndex);
            }

            m_matrix.insert(availableDropPointIndex, object);
            alignObject(m_dropPoints[availableDropPointIndex], object);
        }

        else if(objectDroppedInSameRow)    //move to last position -> don't move
            alignObject(m_dropPoints[m_matrix.key(object)], object);

        else
            unregisterObjectFromMatrix(object);
    }

    catch(const std::overflow_error& ex) {
        qDebug() << ex.what();

        emit rowIsFull(object);
    }

    catch(const std::range_error& ex) {
        qDebug() << ex.what();
        checkDropPointRelease(object);

        emit droppedOutOfGrid(object);
    }
}

void DropGrid::shiftObjectsCurrentDropPoint(int index)
{
    QList<int> dropPointsInRow = DropGridSectionSystem::dropPointsInRow(index, m_matrixSize);
    std::sort(dropPointsInRow.begin(), dropPointsInRow.end());

    if(m_objectsAlign == Qt::AlignRight)
        std::reverse(dropPointsInRow.begin(), dropPointsInRow.end());

    foreach (int i, dropPointsInRow) {
        if(m_matrix[i] != NULL) {
            DropableObject* object = m_matrix[i];

            if(m_objectsAlign == Qt::AlignLeft && i > index) {
                qDebug() << QString("Shifting %1 to %2").arg(i).arg(i-1);
                unregisterObjectFromMatrix(object);
                m_matrix.insert(i - 1, object);
                alignObject(m_dropPoints[i - 1], object);
            }

            else if(m_objectsAlign == Qt::AlignRight && i < index) {
                qDebug() << QString("Shifting %1 to %2 - ").arg(i).arg(i+1) << m_dropPoints[i+1];
                unregisterObjectFromMatrix(object);
                m_matrix.insert(i + 1, object);
                alignObject(m_dropPoints[i + 1], object);
            }
        }
    }
}

void DropGrid::unregisterObjectFromMatrix(DropableObject* object)
{
    int dropPointIndex = m_matrix.key(object);
    m_dropPoints[dropPointIndex]->setTaken(false);
    m_matrix.remove(dropPointIndex);
}

void DropGrid::checkDropPointRelease(DropableObject *object)
{
    //if object is in matrix emit released drop point
    const int dropPointIndex = m_matrix.key(object, -1);
    qDebug() << dropPointIndex;
    if(dropPointIndex + 1)
        emit dropPointReleased(dropPointIndex);
}

int DropGrid::findAvailableDropPoint(DropPoint *closestDropPoint, int alignment)
{
    if(alignment != Qt::AlignLeft && alignment != Qt::AlignRight)
        return -1;

    QList<int> availableDropPointIndexes = DropGridSectionSystem::dropPointsInRow(
                                               m_dropPoints.indexOf(closestDropPoint),
                                               QSize(m_columns, m_rows));
    //remove taken drop points from result
    foreach (int i, availableDropPointIndexes)
        if(m_dropPoints.at(i)->taken())
            availableDropPointIndexes.removeOne(i);

    std::sort(availableDropPointIndexes.begin(), availableDropPointIndexes.end());

    if(!availableDropPointIndexes.length())
        throw std::overflow_error("No droppoint is available.");

    if(alignment == Qt::AlignLeft)
        return availableDropPointIndexes.first();

    else
        return availableDropPointIndexes.last();
}

void DropGrid::alignObject(DropPoint* point, DropableObject *object)
{
    QPointF relativeObjectCenterPoint = GraphicalLogic::relativeCenterPoint(object);
    QPointF dropPointCenter = GraphicalLogic::centerPoint(point);
    QPoint targetDestination = QPoint(
                                   x() + dropPointCenter.x() - relativeObjectCenterPoint.x(),
                                   y() + dropPointCenter.y() - relativeObjectCenterPoint.y());
    point->setTaken(true);
    object->move(targetDestination);
}

void DropGrid::setRows(int rows)
{
    if (m_rows == rows)
        return;

    m_rows = rows;
    m_matrixSize.setHeight(rows);
    emit rowsChanged(rows);
}

void DropGrid::setColumns(int columns)
{
    if (m_columns == columns)
        return;

    m_columns = columns;
    m_matrixSize.setWidth(columns);
    emit columnsChanged(columns);
}

void DropGrid::setObjectsAlign(int objectsAlign)
{
    if (m_objectsAlign == objectsAlign)
        return;

    m_objectsAlign = objectsAlign;
    emit objectsAlignChanged(objectsAlign);
}
