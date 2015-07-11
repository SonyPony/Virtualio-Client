#include "graphgrid.h"
#include "core/interval.h"

GraphGrid::GraphGrid(): AbstractGraphGrid()
{
    connect(this, SIGNAL(horizontalRatioChanged(double)), this, SLOT(resizeAxisX(double)));
    connect(this, SIGNAL(verticalRatioChanged(double)), this, SLOT(resizeAxisY(double)));
}

void GraphGrid::paint(QPainter *painter)
{

}

void GraphGrid::resizeAxisX(double ratio)
{
    m_xAxisLabels = QStringList();
    int piece = m_xAxis->length() / m_xAxisCount * ratio;

    for(int i = 0; i < (int)(m_xAxisCount * ratio); i++)
        m_xAxisLabels.append(QString::number(m_xAxis->min() + i * piece, 'g', 1));
}

void GraphGrid::resizeAxisY(double ratio)
{
    m_yAxisLabels = QStringList();
    int piece = m_yAxis->length() / m_yAxisCount * ratio;

    for(int i = 0; i < (int)(m_yAxisCount * ratio); i++)
        m_yAxisLabels.append(QString::number(m_yAxis->min() + i * piece, 'g', 1));
}

