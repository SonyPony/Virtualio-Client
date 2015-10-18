#ifndef CloneManager_H
#define CloneManager_H

#include <QPointer>
#include <QVector>
#include "clonetag.h"
#include <QObject>
#include <QQuickItem>
#include "tagappearance.h"

/*class CloneManagerSignalSlots: public QObject
{
        Q_OBJECT

    public slots:
        void remove(int index);
};*/

template<typename CloneType>
class CloneManager
{
    private:
        void reindex(int removedIndex);

    protected:
        QVector<QPointer<CloneType> > m_instances;

    public:
        //CloneManager();

        QPointer<CloneType> clone(TagAppearance* appearance, QQuickItem* parent);
        QVector<QPointer<CloneType> > instances() const;

    //public slots:
        //void remove(int index);
};

#include "clonemanager.tcc"
#endif // CloneManager_H
