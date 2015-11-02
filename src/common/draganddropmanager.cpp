#include "draganddropmanager.h"
#include <QPoint>
#include "interval.h"

DragAndDropManager::DragAndDropManager(QQuickItem *component, QObject *parent) : QObject(parent)
{
    m_enabledOrientations = Qt::Horizontal | Qt::Vertical;
    m_pressed = false;
    m_target = component;
}

void DragAndDropManager::setMoveArea(QRectF area)
{
    m_moveArea = area;
}

QSize DragAndDropManager::distanceFromTLCorner() const
{
    return m_distanceFromTLCorner;
}

QRectF DragAndDropManager::moveArea() const
{
    return m_moveArea;
}

void DragAndDropManager::setEnabledOrientations(int orientations)
{
    m_enabledOrientations = orientations;
}

void DragAndDropManager::move(QMouseEvent *event)
{
    this->move(event->pos());
}

void DragAndDropManager::move(QPoint diffPoint)
{
    if(m_moveArea.isEmpty()) {
        if(m_enabledOrientations & Qt::Horizontal)
            m_target->setX(diffPoint.x() + m_target->x() - m_distanceFromTLCorner.width());
        if(m_enabledOrientations & Qt::Vertical)
            m_target->setY(diffPoint.y() + m_target->y() - m_distanceFromTLCorner.height());
    }

    else {
        Interval horizontalArea(m_moveArea.x(), m_moveArea.width());
        Interval verticalArea(m_moveArea.y(), m_moveArea.height());
        double valuePos;

        if(m_enabledOrientations & Qt::Horizontal) {
            valuePos = horizontalArea.valuePos(diffPoint.x() + m_target->x() - m_distanceFromTLCorner.width());
            m_target->setX(horizontalArea.valuePosToValue(valuePos));
        }

        if(m_enabledOrientations & Qt::Vertical) {
            valuePos = verticalArea.valuePos(diffPoint.y() + m_target->y() - m_distanceFromTLCorner.height());
            m_target->setY(verticalArea.valuePosToValue(valuePos));
        }
    }
}

void DragAndDropManager::pressed(QPoint diffPoint)
{
    m_distanceFromTLCorner = QSize(diffPoint.x(), diffPoint.y());
    m_pressed = true;
}

void DragAndDropManager::pressed(QMouseEvent *event)
{
    this->pressed(event->pos());
}

void DragAndDropManager::released()
{
    m_pressed = false;
}

