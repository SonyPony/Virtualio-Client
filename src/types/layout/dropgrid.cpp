#include "dropgrid.h"
#include "dropgridsectionsystem.h"
#include "extentedmath.h"
#include "graphicallogic.h"
#include <stdexcept>
#include <algorithm>
#include "interval.h"
#include <QVector>

DropGrid::DropGrid(QQuickItem* parent): PaintedItem(parent)
{
    m_matrixSize = QSize(0, 0);
    m_matrix = new QMap<int, DropableObject*>;

    connect(this, &QQuickItem::heightChanged, this, &DropGrid::repositionAllDroppedObjects);
    connect(this, &QQuickItem::widthChanged, this, &DropGrid::repositionAllDroppedObjects);
    connect(this, SIGNAL(dropPointReleased(int)), this, SLOT(shiftObjectsCurrentDropPoint(int)));
    connect(this, SIGNAL(columnsChanged(int)), this, SLOT(reinitDropPoints()));
    connect(this, SIGNAL(rowsChanged(int)), this, SLOT(reinitDropPoints()));
}

DropGrid::~DropGrid()
{
    for(QPointer<DropPoint> value: m_dropPoints)
        value->deleteLater();
}

void DropGrid::paint(QPainter *painter)
{
    if(!m_dropPoints.size())    //there is not any DropPoint
        return;

    const double pieceHor = width() / (double)(m_columns);
    const double pieceVer = height() / (double)(m_rows);
    const double protrude = qMin(pieceHor * 0.7, pieceVer * 0.7);
    QVector<QLine> gridLines;

    repositionDropPoints();

    //horizontal lines
    /*for(int i = 0; i < m_rows - 1; i++) {
        double y = pieceVer * (double)(i + 1);
        if(m_objectsAlign == Qt::AlignRight)
            gridLines.append(QLine(pieceHor - protrude, y, width(), y));
        else
            gridLines.append(QLine(0, y, width() - pieceHor + protrude, y));
    }*/

    //vertical lines
    for(int i = 0; i < m_columns - 1; i++) {
        double x = floor(pieceHor * (double)(i + 1)) - 1;
        gridLines.append(QLine(x, pieceVer - protrude, x, height() - pieceVer + protrude));
    }

    painter->setPen(QPen(m_color));
    painter->drawLines(gridLines);
}

bool DropGrid::objectInsideGrid(DropableObject *object)
{
    return ExtentedMath::pointInRect(GraphicalLogic::centerPoint(object).toPoint(), QRect(position().toPoint(), QSize(width(), height())));
}

void DropGrid::registerObject(DropableObject *object)
{
    connect(object, SIGNAL(positionChanged(DropableObject*)), this, SLOT(resendObjectMoveSignal(DropableObject*)));
    connect(object, SIGNAL(dropped(DropableObject*)), this, SLOT(handleObjectDrop(DropableObject*)));
}

void DropGrid::unregisterObject(DropableObject *object)
{
    disconnect(object, SIGNAL(positionChanged(DropableObject*)), this, SLOT(resendObjectMoveSignal(DropableObject*)));
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

void DropGrid::repositionAllDroppedObjects()
{
    const double pieceHor = width() / (double)(m_columns);
    const double pieceVer = height() / (double)(m_rows);
    QPointF dropPointCenter = GraphicalLogic::relativeCenterPoint(m_dropPoints[0]);

    //move to reinit
    for(QPointer<DropPoint> dropPoint: m_dropPoints) {
        int i = m_dropPoints.indexOf(dropPoint);

        dropPoint->setColor(m_color);
        dropPoint->setX(pieceHor * (double)(i % (m_columns - 1) + 1.) - dropPointCenter.x());
        dropPoint->setY(pieceVer * floor(i / (m_columns - 1) + 1.) - dropPointCenter.y());
    }

    //qDebug() << "START REPOSITION-------------------------";
    for(int key: m_matrix->keys()) {
        //qDebug() << "REPOSITION: " << (*m_matrix)[key] << " TO: " << m_dropPoints[key]->position();
        alignObject(m_dropPoints[key], m_matrix->value(key), false);
    }
    //qDebug() << "END REPOSITION-------------------------";

    update();
}

void DropGrid::resendObjectMoveSignal(DropableObject *object)
{
    emit objectMoved(object);
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
        for(QPointer<DropPoint> item: toDelete) {
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


}

void DropGrid::repositionDropPoints()
{
    const QPointF dropPointCenter = GraphicalLogic::relativeCenterPoint(m_dropPoints[0]);
    const double pieceHor = width() / (double)(m_columns);
    const double pieceVer = height() / (double)(m_rows);

    for(QPointer<DropPoint> dropPoint: m_dropPoints) {
        int i = m_dropPoints.indexOf(dropPoint);

        dropPoint->setColor(m_color);
        dropPoint->setX(pieceHor * (double)(i % (m_columns - 1) + 1.) - dropPointCenter.x());
        dropPoint->setY(pieceVer * floor(i / (m_columns - 1) + 1.) - dropPointCenter.y());
    }
}

void DropGrid::handleObjectDrop(DropableObject *object)
{
    try {
        //this can thow range error
        QPair<int, double> closestPoint = getClosestPointIndex(object);

        const int objectKeyInMatrix = m_matrix->key(object, -1);
        const int availableDropPointIndex = findAvailableDropPoint(m_dropPoints[closestPoint.first], objectKeyInMatrix, m_objectsAlign);
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

            m_matrix->insert(availableDropPointIndex, object);
            alignObject(m_dropPoints[availableDropPointIndex], object);
        }
        else if(objectDroppedInSameRow)    //move to last position -> don't move
            alignObject(m_dropPoints[m_matrix->key(object)], object);

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

    for(int i: dropPointsInRow) {
        if(m_matrix->value(i) != NULL) {
            DropableObject* object = m_matrix->value(i);

            if(m_objectsAlign == Qt::AlignLeft && i > index) {
                qDebug() << QString("Shifting %1 to %2").arg(i).arg(i-1);
                unregisterObjectFromMatrix(object);
                m_matrix->insert(i - 1, object);
                alignObject(m_dropPoints[i - 1], object);
            }

            else if(m_objectsAlign == Qt::AlignRight && i < index) {
                qDebug() << QString("Shifting %1 to %2 - ").arg(i).arg(i+1) << m_dropPoints[i+1];
                unregisterObjectFromMatrix(object);
                m_matrix->insert(i + 1, object);
                alignObject(m_dropPoints[i + 1], object);
            }
        }
    }
}

void DropGrid::unregisterObjectFromMatrix(DropableObject* object)
{
    int dropPointIndex = m_matrix->key(object);
    m_dropPoints[dropPointIndex]->setTaken(false);
    m_matrix->remove(dropPointIndex);
}

void DropGrid::checkDropPointRelease(DropableObject *object)
{
    //if object is in matrix emit released drop point
    const int dropPointIndex = m_matrix->key(object, -1);

    if(dropPointIndex + 1)
        emit dropPointReleased(dropPointIndex);
}

QPoint DropGrid::getObjectActualMatrixPos(DropableObject *object)
{
    try {
        QPair<int, double> closestDropPoint = getClosestPointIndex(object);
        return DropGridSectionSystem::dropPointMatrixPos(closestDropPoint.first, m_matrixSize);
    }

    catch(const std::range_error&) {
        return QPoint(-1, -1);
    }
}

int DropGrid::findAvailableDropPoint(DropPoint *closestDropPoint, int objectKeyInMatrix, int alignment)
{
    if(alignment != Qt::AlignLeft && alignment != Qt::AlignRight)
        return -1;

    QList<int> availableDropPointIndexes = DropGridSectionSystem::dropPointsInRow(
                                               m_dropPoints.indexOf(closestDropPoint),
                                               m_matrixSize);
    const bool objectDroppedInSameRow = availableDropPointIndexes.indexOf(objectKeyInMatrix) > -1;
    //remove taken drop points from result
    for(int i: availableDropPointIndexes)
        if(m_dropPoints.at(i)->taken())
            availableDropPointIndexes.removeOne(i);

    std::sort(availableDropPointIndexes.begin(), availableDropPointIndexes.end());

    if(objectDroppedInSameRow)
        return -1;

    if(!availableDropPointIndexes.length())
        throw std::overflow_error("No droppoint is available.");

    if(alignment == Qt::AlignLeft)
        return availableDropPointIndexes.first();

    else
        return availableDropPointIndexes.last();
}

QPair<int, double> DropGrid::getClosestPointIndex(DropableObject *object)
{
    try {
        //this can throw out of range
        const int sectionIndex = DropGridSectionSystem::sectionIndex(
                                     GraphicalLogic::centerPoint(object),
                                     m_matrixSize,
                                     QRectF(x(), y(), width(), height())
                                 );

        const QList<int> dropPointIndexes = DropGridSectionSystem::dropPointIndexes(sectionIndex, m_matrixSize);
        //fixing relative positioning calculation
        QPointF gridPos = this->position();
        //first drop point index, second, object distance from point
        QPair<int, double> closestPoint = qMakePair(-1, INT16_MAX);

        for(int i: dropPointIndexes) {
            double distance = ExtentedMath::distance(
                                   GraphicalLogic::centerPoint(gridPos + m_dropPoints[i]->position(), m_dropPoints[i]->boundingRect().size()) ,
                                   GraphicalLogic::centerPoint(object));

            if(distance < closestPoint.second) {
                closestPoint.first = i;
                closestPoint.second = distance;
            }
        }

        return closestPoint;
    }

    catch(const std::range_error &ex) {
        throw ex;
    }
}

void DropGrid::alignObject(DropPoint* point, DropableObject *object, bool animate)
{
    QPointF relativeObjectCenterPoint = GraphicalLogic::relativeCenterPoint(object);
    QPointF dropPointCenter = GraphicalLogic::centerPoint(point);
    QPoint targetDestination = QPoint(
                                   x() + dropPointCenter.x() - relativeObjectCenterPoint.x(),
                                   y() + dropPointCenter.y() - relativeObjectCenterPoint.y());
    point->setTaken(true);

    object->move(targetDestination, animate);
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
