#ifndef NONINTERACTIVESCROLLBAR_H
#define NONINTERACTIVESCROLLBAR_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPropertyAnimation>

class NonInteractiveScrollBar : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
        Q_PROPERTY(qreal position READ position WRITE setPosition NOTIFY positionChanged)
        Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

    private:
        QColor m_color;
        int m_orientation;
        qreal m_position;
        bool m_active;
        QPropertyAnimation *m_resizeAnimation;

    public:
        NonInteractiveScrollBar();

        virtual void paint(QPainter *painter);

        QColor color() const;
        int orientation() const;
        int position() const;
        bool active() const;

    public slots:
        void setColor(QColor color);
        void setOrientation(int orientation);
        void setPosition(qreal position);
        void setActive(bool active);

    signals:
        void colorChanged(QColor color);
        void orientationChanged(int orientation);
        void positionChanged(qreal position);
        void activeChanged(bool active);
};

#endif // NONINTERACTIVESCROLLBAR_H
