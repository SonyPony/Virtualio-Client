#include "graphcontent.h"

GraphContent::GraphContent(): AbstractGraphContent()
{
    connect(m_horizontalAxis, SIGNAL(propertiesReady()), this, SLOT(update()));
    connect(m_verticalAxis, SIGNAL(propertiesReady()), this, SLOT(update()));
}

void GraphContent::paint(QPainter *painter)
{
    if(m_dataX.length() != m_dataY.length())    //something messed up
        return;

    GraphUtils::GraphOptions options;
    options.color = m_color;
    options.drawSquareLine = true;
    options.squareLineColor = QColor("lightGray");
    options.lineWidth = m_lineWidth;

    QVector<QPointF> points = GraphUtils::calculatePointsPos(data(), m_verticalAxis, m_horizontalAxis);
    GraphUtils::drawGraph(points, QSizeF(width(), height()), options, painter);
}

int GraphContent::lineWidth() const
{
    return m_lineWidth;
}

QColor GraphContent::color() const
{
    return m_color;
}

int GraphContent::contentY() const
{
    return m_contentY;
}

GraphUtils::GraphData GraphContent::data() const
{
    GraphUtils::GraphData gd;
    gd.dataX = m_dataX;
    gd.dataY = m_dataY;

    return gd;
}

QColor GraphContent::squareLineColor() const
{
    return m_squareLineColor;
}

void GraphContent::setLineWidth(int lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    emit lineWidthChanged(lineWidth);
}

void GraphContent::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

void GraphContent::setContentY(int contentY)
{
    if (m_contentY == contentY)
        return;

    m_contentY = contentY;
    emit contentYChanged(contentY);
}

void GraphContent::setSquareLineColor(QColor squareLineColor)
{
    if (m_squareLineColor == squareLineColor)
        return;

    m_squareLineColor = squareLineColor;
    emit squareLineColorChanged(squareLineColor);
}


