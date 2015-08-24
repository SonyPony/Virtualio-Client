#include "dropgrid.h"
#include "dropgridsectionsystem.h"
#include "../../core/extentedmath.h"
#include "../../core/graphicallogic.h"
#include <stdexcept>
#include <QPair>

DropGrid::DropGrid()
{
    m_xAnimation = new QPropertyAnimation(this);
    m_xAnimation->setPropertyName("x");
    m_xAnimation->setDuration(250);
    m_xAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));

    m_yAnimation = new QPropertyAnimation(this);
    m_yAnimation->setPropertyName("y");
    m_yAnimation->setDuration(m_xAnimation->duration());
    m_yAnimation->setEasingCurve(m_xAnimation->easingCurve());

    m_moveAnimation = new QParallelAnimationGroup(this);
    m_moveAnimation->addAnimation(m_xAnimation);
    m_moveAnimation->addAnimation(m_yAnimation);

    m_columns = 5;
    m_rows = 4;
    //QPoint sectionPos;
    for(int i = 0; i < (m_columns - 1) * (m_rows - 1); i++) {
        //sectionPos = DropGridSectionSystem::sectionPos(i, QSize(m_columns, m_rows));

        m_dropPoints.append(new DropPoint(this));
        m_dropPoints[i]->setWidth(10);
        m_dropPoints[i]->setHeight(10);
    }
}

DropGrid::~DropGrid()
{
    m_xAnimation->deleteLater();
    m_yAnimation->deleteLater();
    m_moveAnimation->deleteLater();

    foreach (QPointer<DropPoint> value, m_dropPoints)
        value->deleteLater();
}

void DropGrid::paint(QPainter *painter)
{
    const int pieceHor = width() / (double)m_columns;
    const int pieceVer = height() / (double)m_rows;

    foreach (QPointer<DropPoint> dropPoint, m_dropPoints) {
        int i = m_dropPoints.indexOf(dropPoint);

        dropPoint->setX(pieceHor * (double)(i % (m_columns - 1) + 1.));
        dropPoint->setY(pieceVer * floor(i / (m_columns - 1) + 1.));
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

    m_xAnimation->setTargetObject(object);
    m_xAnimation->setStartValue(object->x());
    m_xAnimation->setEndValue(x() + dropPointCenter.x() - relativeObjectCenterPoint.x());

    m_yAnimation->setTargetObject(object);
    m_yAnimation->setStartValue(object->y());
    m_yAnimation->setEndValue( y() + dropPointCenter.y() - relativeObjectCenterPoint.y());

    m_moveAnimation->start();
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
