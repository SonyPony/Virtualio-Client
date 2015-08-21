#include "draganddropmanager.h"

DragAndDropManager::DragAndDropManager(QQuickItem *component, QObject *parent) : QObject(parent)
{
    m_pressed = false;
    m_target = component;
}

void DragAndDropManager::move(QMouseEvent *event)
{
    m_target->setX(event->x() + m_target->x() - m_distanceFromTLCorner.width());
    m_target->setY(event->y() + m_target->y() - m_distanceFromTLCorner.height());
}

void DragAndDropManager::pressed(QMouseEvent *event)
{
    m_distanceFromTLCorner = QSize(event->x(), event->y());
    m_pressed = true;
}

void DragAndDropManager::released()
{
    m_pressed = false;
}

