#ifndef DROPABLEOBJECT_H
#define DROPABLEOBJECT_H

#include <QQuickItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "painteditem.h"
#include "draganddropmanager.h"

class DropableObject : public PaintedItem
{
        Q_OBJECT
    protected:
        DragAndDropManager *m_dragAndDropManager;
        QPropertyAnimation* m_xAnimation;
        QPropertyAnimation* m_yAnimation;
        QParallelAnimationGroup* m_moveAnimation;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent*);

    public:
        DropableObject(QQuickItem* parent = 0);
        ~DropableObject();

        virtual void paint(QPainter *painter) = 0;

        void move(QPoint position);

    private slots:
        void emitPositionChange();

    public slots:
        virtual void enteredIntoGrid() = 0;
        virtual void leavedFromGrid() = 0;

    signals:
        void positionChanged(DropableObject* object);
        void deleteRequest();
        void dropped(DropableObject* object);
};

#endif // DROPABLEOBJECT_H
