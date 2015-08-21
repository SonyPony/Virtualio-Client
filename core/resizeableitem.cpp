#include "resizeableitem.h"


int ResizeAbleItem::originHeight() const
{
    return m_originHeight;
}
ResizeAbleItem::ResizeAbleItem()
{
    m_verticalRatio = 1;
    m_horizontalRatio = 1;
    m_enabledDirections = ResizeAbleItem::Vertical | ResizeAbleItem::Horizontal;
    connect(this, SIGNAL(verticalRatioChanged(double)), this, SLOT(setOriginHeight()));
    connect(this, SIGNAL(verticalRatioChanged(double)), this, SLOT(update()));
    connect(this, SIGNAL(horizontalRatioChanged(double)), this, SLOT(update()));
}

void ResizeAbleItem::setOriginHeight()
{
    //m_originHeight = height() / m_verticalRatio;
}


double ResizeAbleItem::verticalRatio() const
{
    return m_verticalRatio;
}

double ResizeAbleItem::horizontalRatio() const
{
    return m_horizontalRatio;
}

int ResizeAbleItem::enabledDirections() const
{
    return m_enabledDirections;
}

void ResizeAbleItem::setVerticalRatio(double verticalRatio)
{
    if (m_verticalRatio == verticalRatio || ~m_enabledDirections & ResizeAbleItem::Vertical)
        return;
    double ratio = verticalRatio / m_verticalRatio;
    //setY(y() + (m_verticalRatio - verticalRatio) * height() / m_verticalRatio);
    setHeight(height() * ratio);

    m_verticalRatio = verticalRatio;
    emit verticalRatioChanged(verticalRatio);
}

void ResizeAbleItem::setHorizontalRatio(double horizontalRatio)
{
    if (m_horizontalRatio == horizontalRatio || ~m_enabledDirections & ResizeAbleItem::Horizontal)
        return;
    double ratio = horizontalRatio / m_horizontalRatio;
    setWidth(width() * ratio);

    m_horizontalRatio = horizontalRatio;
    emit horizontalRatioChanged(horizontalRatio);
}

void ResizeAbleItem::setEnabledDirections(int enabledDirections)
{
    if (m_enabledDirections == enabledDirections)
        return;

    m_enabledDirections = enabledDirections;
    emit enabledDirectionsChanged(enabledDirections);
}

