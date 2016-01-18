#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "painteditem.h"
#include <QMouseEvent>
#include <QHoverEvent>

class AbstractButton : public PaintedItem
{
        Q_OBJECT

    protected:
        bool m_pressed;
        bool m_hovered;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void hoverEnterEvent(QHoverEvent* event);
        virtual void hoverLeaveEvent(QHoverEvent* event);

    public:
        AbstractButton(QQuickItem* parent = 0);

        virtual void paint(QPainter*) = 0;

    Q_SIGNALS:
        void clicked(QPoint position);
        void entered();
        void leaved();
};

#endif // ABSTRACTBUTTON_H
