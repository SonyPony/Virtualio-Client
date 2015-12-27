#include "horizontaltabview.h"

HorizontalTabView::HorizontalTabView(QObject *parent) : AbstractTabView(parent)
{

}

void HorizontalTabView::resizeAndRepositionChildrens()
{
    if(!this->width() || !this->height())
        return;

    for(Tab* tab: m_tabs) {
        tab->setX(tab->index() - m_currentTab * this->width());
        tab->setSize(QSizeF(this->width(), this->height()));
    }
}

void HorizontalTabView::moveToTab(int index)
{
    AbstractTabView::moveToTab(index);

    for(int i = 0; i < m_tabs.length(); i++)
        m_tabs[i]->move(QPointF((i - index) * this->width(), m_tabs[i]->y()));
}

