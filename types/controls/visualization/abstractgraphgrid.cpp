#include "abstractgraphgrid.h"
#include <QStringList>

AbstractGraphGrid::AbstractGraphGrid(): ResizeAbleItem()
{

}

Interval *AbstractGraphGrid::xAxis() const
{
    return m_xAxis;
}

Interval *AbstractGraphGrid::yAxis() const
{
    return m_yAxis;
}

int AbstractGraphGrid::xAxisCount() const
{
    return m_xAxisCount;
}

int AbstractGraphGrid::yAxisCount() const
{
    return m_yAxisCount;
}

qreal AbstractGraphGrid::ratio() const
{
    return m_ratio;
}


void AbstractGraphGrid::setXAxis(Interval *xAxis)
{
    if (m_xAxis == xAxis)
        return;

    m_xAxis = xAxis;
    emit xAxisChanged(xAxis);
}

void AbstractGraphGrid::setYAxis(Interval *yAxis)
{
    if (m_yAxis == yAxis)
        return;

    m_yAxis = yAxis;
    emit yAxisChanged(yAxis);
}

void AbstractGraphGrid::setXAxisCount(int xAxisCount)
{
    if (m_xAxisCount == xAxisCount)
        return;

    m_xAxisCount = xAxisCount;
    emit xAxisCountChanged(xAxisCount);
}

void AbstractGraphGrid::setYAxisCount(int yAxisCount)
{
    if (m_yAxisCount == yAxisCount)
        return;

    m_yAxisCount = yAxisCount;
    emit yAxisCountChanged(yAxisCount);
}

void AbstractGraphGrid::setRatio(qreal ratio)
{
    if (m_ratio == ratio)
        return;

    m_ratio = ratio;
    emit ratioChanged(ratio);
}

