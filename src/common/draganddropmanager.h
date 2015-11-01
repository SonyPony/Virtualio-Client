#ifndef DRAGANDDROPMANAGER_H
#define DRAGANDDROPMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QMouseEvent>

class DragAndDropManager : public QObject
{
        Q_OBJECT
    private:
        QQuickItem* m_target;
        bool m_pressed;
        QSize m_distanceFromTLCorner;
        int m_enabledOrientations;

    public:
        DragAndDropManager(QQuickItem* component, QObject *parent = 0);

        QSize distanceFromTLCorner() const;
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
