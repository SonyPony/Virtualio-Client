#ifndef TAGMENUSELECTION_H
#define TAGMENUSELECTION_H

#include <QObject>
#include <QPainter>
#include <QSignalMapper>
#include <types/containers/tagmenuselectionitem.h>
#include "tabselection.h"

class TagMenuSelection : public TabSelection
{
        Q_OBJECT
        Q_PROPERTY(QStringList tabTextColors READ tabTextColors WRITE setTabTextColors NOTIFY tabTextColorsChanged)

    private:
        QStringList m_tabTextColors;
        QSignalMapper* m_signalMapper;
        QList<TagMenuSelectionItem*> m_selectionItems;

    public:
        TagMenuSelection(QObject *parent = 0);

        virtual void paint(QPainter* painter);

        QStringList tabTextColors() const;

    private Q_SLOTS:
        void reinitSelectionItems();

    public Q_SLOTS:
        void setTabTextColors(QStringList tabTextColors);
        void syntheticTabSelect(int index);

    Q_SIGNALS:
        void tabTextColorsChanged(QStringList tabTextColors);
};

#endif // TAGMENUSELECTION_H
