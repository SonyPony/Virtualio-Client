#include "abstracttabselection.h"

AbstractTabSelection::AbstractTabSelection(QQuickItem *parent): m_spacing(0), PaintedItem(parent)
{

}

int AbstractTabSelection::spacing() const
{
    return m_spacing;
}

void AbstractTabSelection::setSpacing(int spacing)
{
    if (m_spacing == spacing)
        return;

    m_spacing = spacing;
    emit spacingChanged(spacing);
}

