#ifndef DROPGRID_H
#define DROPGRID_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointer>
#include <QMap>
#include <QPair>

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
        int m_objectsAlign;
        QMap<int, DropableObject*> m_matrix;
        QSize m_matrixSize;

        int findAvailableDropPoint(DropPoint *closestDropPoint, int objectKeyInMatrix, int alignment);
        QPair<int, double> getClosestPointIndex(DropableObject *object);

    public:
        DropGrid();
        ~DropGrid();

        virtual void paint(QPainter *painter);

        bool objectInsideGrid(DropableObject* object);
        void registerObject(DropableObject* object);
        void unregisterObject(DropableObject* object);
        void unregisterObjectFromMatrix(DropableObject *object);
        void checkDropPointRelease(DropableObject* object);
        QPoint getObjectActualMatrixPos(DropableObject* object);

        int rows() const;
        int columns() const;
        int objectsAlign() const;

    private slots:
        void resendObjectMoveSignal(DropableObject* object);
        void shiftObjectsCurrentDropPoint(int index);
        void reinitDropPoints();
        void handleObjectDrop(DropableObject* object);
        void alignObject(DropPoint *point, DropableObject* object);

    public slots:
        void setRows(int rows);
        void setColumns(int columns);
        void setObjectsAlign(int objectsAlign);

    signals:
        void dropPointReleased(int index);
        void rowIsFull(DropableObject* overflowedObject);
        void droppedOutOfGrid(DropableObject* object);
        void objectMoved(DropableObject* object);

        void rowsChanged(int rows);
        void columnsChanged(int columns);
        void objectsAlignChanged(int objectsAlign);
};

#endif // DROPGRID_H
