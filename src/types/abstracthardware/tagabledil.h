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
#include <types/cloneableobject/tagsselectionmanager.h>

#include <types/layout/tagmatrixmanager.h>
#include <types/layout/tagstrictcombinationwatcher.h>

class TagableDIL : public QQuickPaintedItem
{
        Q_OBJECT
    private:
        DropGridsManager *m_dropGridsManager;
        QMap<QString, DropGrid*> m_dropGrids;
        QSvgRenderer *m_DILRenderer;
        TagsSelectionManager *m_tagSelectionManager;
        TagMatrixManager* m_tagMatrixManager;
        TagStrictCombinationWatcher* m_combinationWatcher;

    public:
        TagableDIL();

        virtual void paint(QPainter* painter);

    private Q_SLOTS:
        void setTagPinNumber(QPoint matrixPos, CloneTag* object);
        void checkValidTagCombinations(CloneTag *currentlyDroppedTag);

    public Q_SLOTS:
        DropGrid* dropGrid(QString side);
        void registerTag(CloneTag* object);
        void disselectAll();
        void serializeTags();

    Q_SIGNALS:
        void selectedTag(QString tagType, QVariantMap tagOptions);
        void disselectedTag(CloneTag* tag);
        void disselected();
};

#endif // TAGABLEDIL_H
