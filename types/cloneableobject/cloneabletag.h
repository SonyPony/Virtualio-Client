#ifndef CLONEABLETAG_H
#define CLONEABLETAG_H

#include "clonemanager.h"
#include "clonetag.h"
#include <QQuickPaintedItem>
#include <QPainter>

class CloneableTag : public QQuickPaintedItem
{
        Q_OBJECT
    protected:
        CloneManager *m_manager;

    public:
        CloneableTag();

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent* event);

    signals:

    public slots:
};

#endif // CLONEABLETAG_H
