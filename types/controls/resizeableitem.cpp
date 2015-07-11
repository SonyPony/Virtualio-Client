#include "resizeableitem.h"

ResizeAbleItem::ResizeAbleItem()
{
    m_horizontalRatio = 1;
    m_verticalRatio = 1;

    connect(this, SIGNAL(verticalRatioChanged(double)), this, SLOT(update()));
    connect(this, SIGNAL(horizontalRatioChanged(double)), this, SLOT(update()));
}

double ResizeAbleItem::verticalRatio() const
{
    return m_verticalRatio;
}

double ResizeAbleItem::horizontalRatio() const
{
    return m_horizontalRatio;
}

void ResizeAbleItem::setVerticalRatio(double verticalRatio)
{
    if (m_verticalRatio == verticalRatio)
        return;

    m_verticalRatio = verticalRatio;
    emit verticalRatioChanged(verticalRatio);
}

void ResizeAbleItem::setHorizontalRatio(double horizontalRatio)
{
    if (m_horizontalRatio == horizontalRatio)
        return;

    m_horizontalRatio = horizontalRatio;
    emit horizontalRatioChanged(horizontalRatio);
}

