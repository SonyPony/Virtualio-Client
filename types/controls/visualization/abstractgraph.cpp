#include "abstractgraph.h"

AbstractGraph::AbstractGraph()
{

}

Interval* AbstractGraph::xAxis() const
{
    return m_xAxis;
}

Interval* AbstractGraph::yAxis() const
{
    return m_yAxis;
}

int AbstractGraph::xAxisStep() const
{
    return m_xAxisStep;
}

int AbstractGraph::yAxisStep() const
{
    return m_yAxisStep;
}

void AbstractGraph::setXAxis(Interval* xAxis)
{
    if (m_xAxis == xAxis)
        return;

    m_xAxis = xAxis;
    emit xAxisChanged(xAxis);
}

void AbstractGraph::setYAxis(Interval* yAxis)
{
    if (m_yAxis == yAxis)
        return;

    m_yAxis = yAxis;
    emit yAxisChanged(yAxis);
}

void AbstractGraph::setXAxisStep(int xAxisStep)
{
    if (m_xAxisStep == xAxisStep)
        return;

    m_xAxisStep = xAxisStep;
    emit xAxisStepChanged(xAxisStep);
}

void AbstractGraph::setYAxisStep(int yAxisStep)
{
    if (m_yAxisStep == yAxisStep)
        return;

    m_yAxisStep = yAxisStep;
    emit yAxisStepChanged(yAxisStep);
}

