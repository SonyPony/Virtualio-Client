#include "tabselection.h"

TabSelection::TabSelection(QObject *parent): AbstractTabSelection((QQuickItem*)parent)
{
}

QFont TabSelection::font() const
{
    return m_font;
}

QStringList TabSelection::tabLabels() const
{
    return m_tabLabels;
}

void TabSelection::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void TabSelection::setTabLabels(QStringList tabLabels)
{
    if (m_tabLabels == tabLabels)
        return;

    m_tabLabels = tabLabels;
    emit tabLabelsChanged(tabLabels);
}


