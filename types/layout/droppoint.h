#ifndef DROPPOINT_H
#define DROPPOINT_H

#include "../../core/painteditem.h"
#include <QPainter>

class DropPoint : public PaintedItem
{
        Q_OBJECT
    public:
        DropPoint(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

    signals:

    public slots:
};

#endif // DROPPOINT_H
