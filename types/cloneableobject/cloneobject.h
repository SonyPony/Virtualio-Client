#ifndef CLONEOBJECT_H
#define CLONEOBJECT_H

#include <QQuickPaintedItem>
#include "../../core/draganddropmanager.h"

class CloneObject : public QQuickPaintedItem
{
        Q_OBJECT
    protected:
        int m_index;
        DragAndDropManager *m_dragAndDropManager;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent*);

    public:
        CloneObject();
        CloneObject(int index, QObject* parent);
        ~CloneObject();

        virtual void paint(QPainter *painter) = 0;

        int index() const;
        void setIndex(int value);

    signals:
        void deleteRequest(int index);
};

#endif // CLONEOBJECT_H
