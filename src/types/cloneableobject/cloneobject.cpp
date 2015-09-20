#include "cloneobject.h"
#include <QCursor>

void CloneObject::mousePressEvent(QMouseEvent *event)
{
    DropableObject::mousePressEvent(event);
}

CloneObject::CloneObject(int index, QQuickItem *parent): DropableObject(parent)
{
    m_index = index;
    setCursor(QCursor(Qt::SizeAllCursor));
    update();

    connect(this, SIGNAL(deleteRequest()), this, SLOT(handleDeleteRequestWithoutIndex()));
}

int CloneObject::index() const
{
    return m_index;
}

void CloneObject::setIndex(int value)
{
    m_index = value;
}

void CloneObject::handleDeleteRequestWithoutIndex()
{
    emit deleteRequest(m_index);
}

