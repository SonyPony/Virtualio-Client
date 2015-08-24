#ifndef CLONEABLETAG_H
#define CLONEABLETAG_H

#include "clonemanager.h"
#include "clonetag.h"
#include "../../core/painteditem.h"
#include "../layout/dropgrid.h"
#include <QQuickPaintedItem>
#include <QPainter>

class CloneableTag : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(DropGrid* dropGrid READ dropGrid WRITE setDropGrid NOTIFY dropGridChanged)

    protected:
        CloneManager *m_manager;
        DropGrid* m_dropGrid;

    public:
        CloneableTag();

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent*);

        DropGrid* dropGrid() const;

    public slots:
        void setDropGrid(DropGrid* dropGrid);

    signals:
        void dropGridChanged(DropGrid* dropGrid);
};

#endif // CLONEABLETAG_H
