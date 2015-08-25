#ifndef DROPGRID_H
#define DROPGRID_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "../../core/painteditem.h"
#include "../../core/dropableobject.h"
#include "droppoint.h"

class DropGrid : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
        Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
        Q_PROPERTY(int objectsAlign READ objectsAlign WRITE setObjectsAlign NOTIFY objectsAlignChanged)

    private:
        int m_rows;
        int m_columns;
        QList<QPointer<DropPoint> > m_dropPoints;
        QPropertyAnimation* m_xAnimation;
        QPropertyAnimation* m_yAnimation;
        QParallelAnimationGroup* m_moveAnimation;
        int m_objectsAlign;

    public:
        DropGrid();
        ~DropGrid();

        virtual void paint(QPainter *painter);

        void registerObject(DropableObject* object);
        void unregisterObject(DropableObject* object);

        int rows() const;
        int columns() const;
        int objectsAlign() const;

    private slots:
        void reinitDropPoints();
        void handleObjectDrop(DropableObject* object);
        void alignObject(DropPoint *point, DropableObject* object);

    public slots:
        void setRows(int rows);
        void setColumns(int columns);
        void setObjectsAlign(int objectsAlign);

    signals:
        void rowsChanged(int rows);
        void columnsChanged(int columns);
        void objectsAlignChanged(int objectsAlign);
};

#endif // DROPGRID_H
