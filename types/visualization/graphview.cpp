#include "graphview.h"

GraphView::GraphView()
{
    //connect(m_graph, SIGNAL())
}

void GraphView::paint(QPainter *painter)
{
    //COPYING AND PREPARING DATA
    GraphAxis *vAxis = new GraphAxis(m_graph->verticalAxis());
    GraphAxis *hAxis = new GraphAxis(m_graph->horizontalAxis());
    vAxis->setHeight(height());
    hAxis->setWidth(width());
    QList<double> dataX = m_graph->dataX();
    QList<double> dataY = m_graph->dataY();
    double vRatio = height() / vAxis->height();
    double hRatio = width() / hAxis->width();

    //DRAW GRAPH POINTS
    QPainterPath path;
    QPainterPath fillPath;
    QPoint point;
    painter->setPen(QPen(m_color, m_lineWidth));
    QPointF firstPoint = QPointF(
                hAxis->calculatePointPos(dataX[0]).x() * hRatio,
                vAxis->calculatePointPos(dataY[0]).y() * vRatio);
    path.moveTo(firstPoint);      //start at first point

    for(int i = 0; i < dataX.length(); i++) {
        point = QPoint(
                    hAxis->calculatePointPos(dataX[i]).x() * hRatio,
                    vAxis->calculatePointPos(dataY[i]).y() * vRatio);
        path.lineTo(QPointF(point));
    }

    //close polygon
    fillPath = path;
    fillPath.lineTo(point.x(), height());
    fillPath.lineTo(firstPoint.x(), height());
    fillPath.lineTo(firstPoint);

    painter->setPen(QPen(m_lineColor, m_lineWidth));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPath(path);
    painter->fillPath(fillPath, QBrush(QColor(
                                           m_lineColor.red(),
                                           m_lineColor.green(),
                                           m_lineColor.blue(),
                                           50)));
    delete vAxis;
    delete hAxis;
    vAxis = NULL;
    hAxis = NULL;
}

GraphContent* GraphView::graph() const
{
    return m_graph;
}

QColor GraphView::lineColor() const
{
    return m_lineColor;
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

void GraphView::setLineColor(QColor lineColor)
{
    if (m_lineColor == lineColor)
        return;

    m_lineColor = lineColor;
    emit lineColorChanged(lineColor);
}

void GraphView::setLineWidth(int lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    emit lineWidthChanged(lineWidth);
}
