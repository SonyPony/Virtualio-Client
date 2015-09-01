#ifndef DROPGRIDSMANAGER_H
#define DROPGRIDSMANAGER_H

#include <QObject>
#include "dropgrid.h"
#include "../../core/dropableobject.h"

class DropGridsManager : public QObject
{
        Q_OBJECT
    private:
        QList<DropGrid *> m_dropGrids;

    public:
        explicit DropGridsManager(QObject *parent = 0);

        void registerGrid(DropGrid* grid);
        void unregisterGrid(DropGrid* grid);

        QList<DropGrid *> dropGrids() const;

    private slots:
        void unregisterObject(DropableObject *object);
        void unblockDropGridSignal();
        void checkObjectDrop(DropableObject *object);
};

#endif // DROPGRIDSMANAGER_H
