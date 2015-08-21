#include "cloneobject.h"
#include <QCursor>

void CloneObject::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        emit deleteRequest(m_index);
    else
        m_dragAndDropManager->pressed(event);
}

void CloneObject::mouseMoveEvent(QMouseEvent *event)
{
    m_dragAndDropManager->move(event);
}

void CloneObject::mouseReleaseEvent(QMouseEvent *)
{
    m_dragAndDropManager->released();
    ungrabMouse();
}

CloneObject::CloneObject()
{
    setAcceptHoverEvents(true);
    setCursor(QCursor(Qt::SizeAllCursor));
}

CloneObject::CloneObject(int index, QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    m_index = index;
    m_dragAndDropManager = new DragAndDropManager(this);
    update();
}

CloneObject::~CloneObject()
{
    delete m_dragAndDropManager;
    m_dragAndDropManager = NULL;
}

int CloneObject::index() const
{
    return m_index;
}

void CloneObject::setIndex(int value)
{
    m_index = value;
}

