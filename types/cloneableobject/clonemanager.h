#ifndef CloneManager_H
#define CloneManager_H

#include <QPointer>
#include <QVector>
#include "clonetag.h"

class CloneManager : public QObject
{
    Q_OBJECT

    private:
        void reindex(int removedIndex);

    protected:
        QVector<QPointer<CloneTag> > m_instances;

    public:
        CloneManager();

        QPointer<CloneTag> clone(QQuickItem* parent);
        QVector<QPointer<CloneTag> > instances() const;

    public slots:
        void remove(int index);
};

#endif // CloneManager_H
