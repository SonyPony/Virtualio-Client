#ifndef TAGABLEDIL_H
#define TAGABLEDIL_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPoint>
#include <QMap>
#include <QSize>
#include <QSvgRenderer>

#include "../cloneableobject/clonetag.h"
#include "../layout/dropgridsmanager.h"
#include "../layout/dropgrid.h"

class TagableDIL : public QQuickPaintedItem
{
        Q_OBJECT
    private:
        DropGridsManager *m_dropGridsManager;
        QMap<QString, DropGrid*> m_dropGrids;
        QSvgRenderer *m_DILRenderer;

    public:
        TagableDIL();

        virtual void paint(QPainter* painter);

    private slots:
        void setTagPinNumber(QPoint matrixPos, CloneTag* object);

    public slots:
        DropGrid* dropGrid(QString side);
        void registerTag(CloneTag* object);

    signals:

};

#endif // TAGABLEDIL_H
