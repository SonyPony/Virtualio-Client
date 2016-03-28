#ifndef TAGSSELECTIONMANAGER_H
#define TAGSSELECTIONMANAGER_H

#include "clonetag.h"

#include <QObject>
#include <QPointer>
#include <QSignalMapper>

class TagsSelectionManager : public QObject
{
        Q_OBJECT
    private:
        QList<QPointer<CloneTag> > m_tags;
        QSignalMapper* m_signalMapper;
        QPointer<CloneTag> m_lastSelectedTag;
        int m_selectedIndex;

    public:
        TagsSelectionManager(QObject *parent = 0);

        QPointer<CloneTag> lastSelectedTag() const;

    private Q_SLOTS:
        void handleTagSelection(int index);
        void removeGarbage();
        void remapTags();
        void handleSelectedTagDestruction();

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
