#include "graphview.h"
#include "graphutils.h"

GraphView::GraphView(QQuickItem *parent): PaintedItem(parent)
{
}

void GraphView::paint(QPainter *painter)
{
    // COPYING AND PREPARING DATA
    GraphAxis *vAxis = new GraphAxis(m_graph->verticalAxis());
    GraphAxis *hAxis = new GraphAxis(m_graph->horizontalAxis());
    vAxis->setHeight(height());
    hAxis->setWidth(width());

    GraphUtils::GraphOptions options;
    options.color = m_color;
    options.drawSquareLine = false;
    options.lineWidth = m_lineWidth;

    QVector<QPointF> points = GraphUtils::calculatePointsPos(m_graph->data(), vAxis, hAxis);
    GraphUtils::drawGraph(points, QSize(width(), height()), options, painter);
}

GraphContent* GraphView::graph() const
{
    return m_graph;
}

int GraphView::lineWidth() const
{
    return m_lineWidth;
}

void GraphView::setGraph(GraphContent* graph)
{
    if (m_graph == graph)
        return;

    m_graph = graph;
    emit graphChanged(graph);
}

void GraphView::setLineWidth(int lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    emit lineWidthChanged(lineWidth);
}
