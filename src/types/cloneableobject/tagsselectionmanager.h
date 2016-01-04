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
        CloneTag* m_lastSelectedTag;

    public:
        TagsSelectionManager(QObject *parent = 0);

    public Q_SLOTS:
        void registerTag(CloneTag* tag);
        void unregisterTag(CloneTag* tag);
        void disselectAll();

    Q_SIGNALS:
        void selected(CloneTag* tag);
        void disselected(CloneTag* tag);
        void disselectedAll();
};

#endif // TAGSSELECTIONMANAGER_H
