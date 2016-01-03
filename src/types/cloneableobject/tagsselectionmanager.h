#ifndef TAGSSELECTIONMANAGER_H
#define TAGSSELECTIONMANAGER_H

#include "clonetag.h"

#include <QObject>
#include <QSignalMapper>

class TagsSelectionManager : public QObject
{
        Q_OBJECT
    private:
        QList<CloneTag*> m_tags;
        QSignalMapper* m_signalMapper;

    public:
        TagsSelectionManager(QObject *parent = 0);

    public Q_SLOTS:
        void registerTag(CloneTag* tag);
        void unregisterTag(CloneTag* tag);

    Q_SIGNALS:
        void selected(CloneTag* tag);
};

#endif // TAGSSELECTIONMANAGER_H
