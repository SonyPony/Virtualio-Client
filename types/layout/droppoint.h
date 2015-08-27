#ifndef DROPPOINT_H
#define DROPPOINT_H

#include "../../core/painteditem.h"
#include <QPainter>

class DropPoint : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(bool taken READ taken WRITE setTaken NOTIFY takenChanged)

    private:
        bool m_taken;

    public:
        DropPoint(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        bool taken() const;

    public slots:
        void setTaken(bool taken);

    signals:
        void takenChanged(bool taken);
};

#endif // DROPPOINT_H
