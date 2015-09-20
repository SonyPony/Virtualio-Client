#ifndef NONINTERACTIVESCROLLBAR_H
#define NONINTERACTIVESCROLLBAR_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPropertyAnimation>

#include "painteditem.h"

class NonInteractiveScrollBar : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
        Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)
        Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

    private:
        int m_orientation;
        qreal m_position;
        bool m_active;
        QPropertyAnimation *m_resizeAnimation;

    public:
        NonInteractiveScrollBar();

        virtual void paint(QPainter *painter);

        int orientation() const;
        int position() const;
        bool active() const;

    public slots:
        void setOrientation(int orientation);
        void setPosition(qreal position);
        void setActive(bool active);

    signals:
        void orientationChanged(int orientation);
        void positionChanged(qreal position);
        void activeChanged(bool active);
};

#endif // NONINTERACTIVESCROLLBAR_H
