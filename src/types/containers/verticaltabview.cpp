#include "verticaltabview.h"

VerticalTabView::VerticalTabView(QQuickItem *parent): AbstractTabView(parent)
{

}

void VerticalTabView::resizeAndRepositionChildrens()
{
    if(!width() || !height())
        return;

    for(Tab* tab: m_tabs) {
        tab->setY((tab->index() - m_currentTab) * height());
        tab->setSize(QSizeF(width(), height()));
    }
}

void VerticalTabView::moveToTab(int index)
{
    AbstractTabView::moveToTab(index);

    for(int i = 0; i < m_tabs.length(); i++)
        m_tabs[i]->move(QPointF(m_tabs[i]->x(), (i - index) * height()));
}

