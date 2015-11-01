#include "draganddropmanager.h"
#include <QPoint>

DragAndDropManager::DragAndDropManager(QQuickItem *component, QObject *parent) : QObject(parent)
{
    m_enabledOrientations = Qt::Horizontal | Qt::Vertical;
    m_pressed = false;
    m_target = component;
}

QSize DragAndDropManager::distanceFromTLCorner() const
{
    return m_distanceFromTLCorner;
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
    if(m_enabledOrientations & Qt::Horizontal)
        m_target->setX(diffPoint.x() + m_target->x() - m_distanceFromTLCorner.width());
    if(m_enabledOrientations & Qt::Vertical)
        m_target->setY(diffPoint.y() + m_target->y() - m_distanceFromTLCorner.height());
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

