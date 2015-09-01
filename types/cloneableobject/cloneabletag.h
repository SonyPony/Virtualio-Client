#ifndef CLONEABLETAG_H
#define CLONEABLETAG_H

#include "clonemanager.h"
#include "clonetag.h"
#include "../../core/painteditem.h"
#include "../layout/dropgridsmanager.h"
#include <QQuickPaintedItem>
#include <QPainter>

class CloneableTag : public PaintedItem
{
        Q_OBJECT

    protected:
        CloneManager *m_manager;
        DropGridsManager* m_dropGridManager;

    public:
        CloneableTag();

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent*);

    public slots:
        void registerDropGrid(DropGrid* grid);
        void unregisterDropGrid(DropGrid* grid);

};

#endif // CLONEABLETAG_H
