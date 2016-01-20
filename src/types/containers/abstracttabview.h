#ifndef ABSTRACTTABVIEW_H
#define ABSTRACTTABVIEW_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QList>
#include "tab.h"

class AbstractTabView : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int currentTab READ currentTab NOTIFY currentTabChanged)

    protected:
        QList<Tab*> m_tabs;
        int m_currentTab;

    public:
        AbstractTabView(QObject *parent = 0);

        virtual void paint(QPainter* painter) = 0;

        int currentTab() const;

    private slots:
        void registerChild();
        virtual void resizeAndRepositionChildrens() = 0;

    public slots:
        virtual void addTab(QQuickItem* item);
        virtual void removeTab(QQuickItem* item);
        virtual void moveToTab(int index);
    signals:
        void currentTabChanged(int currentTab);
};

#endif // ABSTRACTTABVIEW_H
