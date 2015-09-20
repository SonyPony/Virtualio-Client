#ifndef CLONEOBJECT_H
#define CLONEOBJECT_H

#include <QQuickPaintedItem>
#include "dropableobject.h"

class CloneObject : public DropableObject
{
        Q_OBJECT
    protected:
        int m_index;

        virtual void mousePressEvent(QMouseEvent* event);

    public:
        CloneObject(int index, QQuickItem* parent);
        ~CloneObject() {}

        virtual void paint(QPainter *painter) = 0;

        int index() const;
        void setIndex(int value);

    private slots:
        void handleDeleteRequestWithoutIndex();

    signals:
        void deleteRequest(int index);
};

#endif // CLONEOBJECT_H
