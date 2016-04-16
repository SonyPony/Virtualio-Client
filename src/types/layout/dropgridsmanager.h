#ifndef DROPGRIDSMANAGER_H
#define DROPGRIDSMANAGER_H

#include <QObject>
#include "dropgrid.h"
#include "dropableobject.h"

class DropGridsManager : public QObject
{
        Q_OBJECT
    private:
        QList<DropGrid *> m_dropGrids;
        QQuickItem* m_objectsParent;

    public:
        explicit DropGridsManager(QObject *parent = 0);

        void setObjectsParent(QQuickItem *parent);
        void registerGrid(DropGrid* grid);
        void unregisterGrid(DropGrid* grid);

        QList<DropGrid *> dropGrids() const;

    private Q_SLOTS:
        void unblockDropGridSignal();
        void checkObjectDrop(DropableObject *object);
        void checkObjectMove(DropableObject *object);
        void emitRowIsFull();
        void emitDroppedOutOfGrid();

    public Q_SLOTS:
        void registerObject(DropableObject* object);
        void unregisterObject(DropableObject *object);

    Q_SIGNALS:
        void tagDeleted(QString msg);
};

#endif // DROPGRIDSMANAGER_H
