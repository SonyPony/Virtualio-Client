#include "dropableobject.h"
#include <QCursor>

DropableObject::DropableObject(QQuickItem* parent): PaintedItem(parent)
{
    m_dragAndDropManager = new DragAndDropManager(this);
    setCursor(QCursor(Qt::SizeAllCursor));

    m_xAnimation = new QPropertyAnimation(this, "x", this);
    m_xAnimation->setDuration(250);
    m_xAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));

    m_yAnimation = new QPropertyAnimation(this, "y", this);
    m_yAnimation->setDuration(m_xAnimation->duration());
    m_yAnimation->setEasingCurve(m_xAnimation->easingCurve());

    m_moveAnimation = new QParallelAnimationGroup(this);
    m_moveAnimation->addAnimation(m_xAnimation);
    m_moveAnimation->addAnimation(m_yAnimation);

    connect(this, SIGNAL(xChanged()), this, SLOT(emitPositionChange()));
    connect(this, SIGNAL(yChanged()), this, SLOT(emitPositionChange()));
}

DropableObject::~DropableObject()
{
    delete m_dragAndDropManager;
    m_dragAndDropManager = NULL;

    m_xAnimation->deleteLater();
    m_yAnimation->deleteLater();
    m_moveAnimation->deleteLater();
}

void DropableObject::move(QPoint position)
{
    m_xAnimation->setStartValue(x());
    m_xAnimation->setEndValue(position.x());

    m_yAnimation->setStartValue(y());
    m_yAnimation->setEndValue(position.y());

    m_moveAnimation->start();
}

void DropableObject::emitPositionChange()
{
    emit positionChanged(this);
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
