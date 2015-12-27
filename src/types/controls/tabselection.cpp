#include "tabselection.h"

TabSelection::TabSelection(QObject *parent): PaintedItem(parent), m_spacing(0)
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

int TabSelection::spacing() const
{
    return m_spacing;
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

void TabSelection::setSpacing(int spacing)
{
    if (m_spacing == spacing)
        return;

    m_spacing = spacing;
    emit spacingChanged(spacing);
}

