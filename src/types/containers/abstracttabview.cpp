#include "abstracttabview.h"
#include "interval.h"

AbstractTabView::AbstractTabView(QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    setClip(true);
    m_currentTab = 0;
    connect(this, SIGNAL(widthChanged()), this, SLOT(resizeAndRepositionChildrens()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(resizeAndRepositionChildrens()));
    connect(this, SIGNAL(childrenChanged()), this, SLOT(registerChild()));
}

int AbstractTabView::currentTab() const
{
    return m_currentTab;
}

void AbstractTabView::registerChild()
{
    for(QQuickItem* child: childItems()) {
        Q_ASSERT(child->inherits("Tab"));
        if(child->property("index") == -1)
            this->addTab(child);
    }
}

void AbstractTabView::addTab(QQuickItem *item)
{
    Q_ASSERT(item->inherits("Tab"));

    Tab* result = (Tab*)item;
    result->setParent(this);
    result->setSize(QSizeF(width(), height()));
    result->setIndex(m_tabs.length());
    m_tabs.append(result);
}

void AbstractTabView::removeTab(QQuickItem *item)
{
    Q_ASSERT(item->inherits("Tab"));

    Tab* result = (Tab*)item;
    m_tabs.removeAll(result);
    result->deleteLater();

    //reindex
    for(Tab* tab: m_tabs)
        tab->setProperty("index", m_tabs.indexOf(tab));
}

void AbstractTabView::moveToTab(int index)
{
    Q_ASSERT(Interval::isIn(0, m_tabs.length() - 1, index));

    if(m_currentTab == index)
        return;

    m_currentTab = index;
    Q_EMIT this->currentTabChanged(index);
}

int AbstractTabView::tabsCount() const
{
    return m_tabs.length();
}

