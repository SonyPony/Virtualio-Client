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

    public:
        DragAndDropManager(QQuickItem* component, QObject *parent = 0);

        void move(QMouseEvent* event);
        void pressed(QMouseEvent* event);
        void released();
};

#endif // DRAGANDDROPMANAGER_H
