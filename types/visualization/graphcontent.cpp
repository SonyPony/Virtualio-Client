#include "graphcontent.h"
#include <QPainterPath>

QPoint GraphContent::combinePoints(QPoint verAxis, QPoint horAxis)
{
    return QPoint(horAxis.x(), verAxis.y());
}

GraphContent::GraphContent(): AbstractGraphContent()
{
    connect(this, SIGNAL(contentYChanged(int)), this, SLOT(update()));
    connect(m_horizontalAxis, SIGNAL(propertiesReady()), this, SLOT(update()));
    connect(m_verticalAxis, SIGNAL(propertiesReady()), this, SLOT(update()));
}

void GraphContent::paint(QPainter *painter)
{
    if(m_dataX.length() != m_dataY.length())    //something messed up
        return;

    //DRAW GRAPH POINTS
    QPainterPath path;
    QPainterPath fillPath;
    QPoint point;
    double markSquareSize = 6;
    QPointF firstPoint = QPointF(combinePoints(
                             m_verticalAxis->calculatePointPos(m_dataY[0]),
                             m_horizontalAxis->calculatePointPos(m_dataX[0])));
    path.moveTo(firstPoint);      //start at first point

    for(int i = 0; i < m_dataX.length(); i++) {
        point = combinePoints(
                    m_verticalAxis->calculatePointPos(m_dataY[i]),
                    m_horizontalAxis->calculatePointPos(m_dataX[i]));
        path.lineTo(QPointF(point));
        painter->fillRect(QRectF(point.x() - markSquareSize / 2., m_contentY, markSquareSize, markSquareSize), QBrush(m_color));
    }

    //close polygon
    fillPath = path;
    fillPath.lineTo(point.x(), height());
    fillPath.lineTo(firstPoint.x(), height());
    fillPath.lineTo(firstPoint);

    painter->setPen(QPen(m_color, m_lineWidth));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPath(path);
    painter->fillPath(fillPath, QBrush(QColor(
                                           m_color.red(),
                                           m_color.green(),
                                           m_color.blue(),
                                           50)));
}

int GraphContent::lineWidth() const
{
    return m_lineWidth;
}

QColor GraphContent::color() const
{
    return m_color;
}

QColor GraphContent::fillColor() const
{
    return m_fillColor;
}

int GraphContent::contentY() const
{
    return m_contentY;
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

void GraphContent::setFillColor(QColor fillColor)
{
    if (m_fillColor == fillColor)
        return;

    m_fillColor = fillColor;
    emit fillColorChanged(fillColor);
}

void GraphContent::setContentY(int contentY)
{
    if (m_contentY == contentY)
        return;

    m_contentY = contentY;
    emit contentYChanged(contentY);
}


