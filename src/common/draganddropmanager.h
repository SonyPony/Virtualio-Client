#ifndef DRAGANDDROPMANAGER_H
#define DRAGANDDROPMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QMouseEvent>
#include <QRectF>

class DragAndDropManager : public QObject
{
        Q_OBJECT
    private:
        QQuickItem* m_target;
        bool m_pressed;
        QSize m_distanceFromTLCorner;
        int m_enabledOrientations;
        QRectF m_moveArea;

    public:
        DragAndDropManager(QQuickItem* component, QObject *parent = 0);

        QSize distanceFromTLCorner() const;
        QRectF moveArea() const;

    public Q_SLOTS:
        void setMoveArea(QRectF area);
        void setEnabledOrientations(int orientations);
        // can be used only if it's called from component::mouseMoveEvent
        void move(QMouseEvent* event);
        void move(QPoint diffPoint);
        // can be used only if it's called from component::mousePressEvent
        void pressed(QMouseEvent* event);
        void pressed(QPoint diffPoint);
        void released();
};

#endif // DRAGANDDROPMANAGER_H
