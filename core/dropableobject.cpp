#include "dropableobject.h"
#include <QCursor>

DropableObject::DropableObject(QQuickItem* parent): PaintedItem(parent)
{
    m_dragAndDropManager = new DragAndDropManager(this);
    setCursor(QCursor(Qt::SizeAllCursor));
}

DropableObject::~DropableObject()
{
    delete m_dragAndDropManager;
    m_dragAndDropManager = NULL;
}

void DropableObject::mousePressEvent(QMouseEvent *event)
{
    m_dragAndDropManager->pressed(event);
}

void DropableObject::mouseMoveEvent(QMouseEvent *event)
{
    m_dragAndDropManager->move(event);
}

void DropableObject::mouseReleaseEvent(QMouseEvent *)
{
    m_dragAndDropManager->released();
    ungrabMouse();

    emit dropped(this);
}
