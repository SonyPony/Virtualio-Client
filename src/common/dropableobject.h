#ifndef DROPABLEOBJECT_H
#define DROPABLEOBJECT_H

#include <QQuickItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPoint>

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
        QPoint m_matrixPosition;
        bool m_locked;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent*);

    public:
        DropableObject(QQuickItem* parent = 0);
        ~DropableObject();

        virtual void paint(QPainter *painter) = 0;

        void move(QPoint position, bool animate=true);
        QPoint matrixPosition() const;
        bool locked() const;

    private slots:
        void emitPositionChange();

    public slots:
        virtual void enteredIntoGrid() = 0;
        virtual void leavedFromGrid() = 0;
        void setMatrixPosition(QPoint value);
        void lock();
        void unlock();

    signals:
        void catched();
        void positionChanged(DropableObject* object);
        void deleteRequest();
        void dropped(DropableObject* object);
        void aligned(QPoint matrixPos, DropableObject* object);
        void matrixPositionChanged(QPoint value);
};

#endif // DROPABLEOBJECT_H
