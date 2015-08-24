#ifndef DROPABLEOBJECT_H
#define DROPABLEOBJECT_H

#include <QQuickItem>
#include "painteditem.h"
#include "draganddropmanager.h"

class DropableObject : public PaintedItem
{
        Q_OBJECT
    protected:
        DragAndDropManager *m_dragAndDropManager;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent*);

    public:
        DropableObject(QQuickItem* parent = 0);
        ~DropableObject();

        virtual void paint(QPainter *painter) = 0;

    signals:
        void deleteRequest();
        void dropped(DropableObject* object);
};

#endif // DROPABLEOBJECT_H
