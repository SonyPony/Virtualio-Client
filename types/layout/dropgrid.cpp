#include "dropgrid.h"
#include "dropgridsectionsystem.h"
#include "../../core/extentedmath.h"
#include "../../core/graphicallogic.h"
#include <stdexcept>
#include "../../core/interval.h"
#include <QPair>

DropGrid::DropGrid()
{

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

    const int pieceHor = width() / (double)m_columns;
    const int pieceVer = height() / (double)m_rows;

    foreach (QPointer<DropPoint> dropPoint, m_dropPoints) {
        int i = m_dropPoints.indexOf(dropPoint);
        QPointF dropPointCenter = GraphicalLogic::relativeCenterPoint(dropPoint);

        dropPoint->setX(pieceHor * (double)(i % (m_columns - 1) + 1.) - dropPointCenter.x());
        dropPoint->setY(pieceVer * floor(i / (m_columns - 1) + 1.) - dropPointCenter.y());
    }

    painter->setPen(QPen("red"));
    painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));

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
            m_dropPoints[i]->setWidth(10);
            m_dropPoints[i]->setHeight(10);
        }
    }

    update();
}

void DropGrid::handleObjectDrop(DropableObject *object)
{
    try {
        const QSize matrixSize(m_columns, m_rows);
        const int sectionIndex = DropGridSectionSystem::sectionIndex(
                                     GraphicalLogic::centerPoint(object),
                                     matrixSize,
                                     QRectF(x(), y(), width(), height())
                                 );
        const QList<int> dropPointIndexes = DropGridSectionSystem::dropPointIndexes(sectionIndex, matrixSize);
        //fixing relative positioning calculation
        QPointF gridPos = this->position();
        QPair<int, double> closestPoint = qMakePair(-1, INT16_MAX);

        foreach (int i, dropPointIndexes) {
            double distance =  ExtentedMath::distance(
                                   GraphicalLogic::centerPoint(gridPos + m_dropPoints[i]->position(), m_dropPoints[i]->boundingRect().size()) ,
                                   GraphicalLogic::centerPoint(object));

            if(distance < closestPoint.second) {
                closestPoint.first = i;
                closestPoint.second = distance;
            }
        }

        alignObject(m_dropPoints[closestPoint.first], object);
    }

    catch(const std::out_of_range& ex) {
        qDebug() << ex.what();
        //delete object dropped out of grid
        unregisterObject(object);
        object->deleteRequest();
    }
}

void DropGrid::alignObject(DropPoint* point, DropableObject *object)
{
    QPointF relativeObjectCenterPoint = GraphicalLogic::relativeCenterPoint(object);
    QPointF dropPointCenter = GraphicalLogic::centerPoint(point);



}

void DropGrid::setRows(int rows)
{
    if (m_rows == rows)
        return;

    m_rows = rows;
    emit rowsChanged(rows);
}

void DropGrid::setColumns(int columns)
{
    if (m_columns == columns)
        return;

    m_columns = columns;
    emit columnsChanged(columns);
}

void DropGrid::setObjectsAlign(int objectsAlign)
{
    if (m_objectsAlign == objectsAlign)
        return;

    m_objectsAlign = objectsAlign;
    emit objectsAlignChanged(objectsAlign);
}
