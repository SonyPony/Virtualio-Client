#ifndef DROPPOINT_H
#define DROPPOINT_H

#include "painteditem.h"
#include <QPainter>

class DropPoint : public PaintedItem
{
        Q_OBJECT

    private:
        bool m_taken;

    public:
        DropPoint(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        bool taken() const;

    public Q_SLOTS:
        void setTaken(bool taken);

    Q_SIGNALS:
        void takenChanged(bool taken);
};

#endif // DROPPOINT_H
