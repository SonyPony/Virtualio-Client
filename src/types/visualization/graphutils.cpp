#include "graphutils.h"
#include <QPainterPath>

QVector<QPointF> GraphUtils::calculatePointsPos(GraphUtils::GraphData data, GraphAxis *vAxis, GraphAxis *hAxis)
{
    QVector<QPointF> points;
    for(int i = 0; i < data.dataX.length(); i++) {
        QPointF point = QPointF(
                    hAxis->calculatePointPos(data.dataX[i]).x(),
                    vAxis->calculatePointPos(data.dataY[i]).y());
        points.append(point);
    }

    return points;
}


void GraphUtils::drawGraph(QVector<QPointF> points, QSizeF graphSize, GraphUtils::GraphOptions options, QPainter *painter)
{
    // DRAW GRAPH POINTS
    QPainterPath path;
    QPainterPath fillPath;
    QPainterPath squarePath;

    squarePath.moveTo(points.first());
    path.moveTo(points.first());      // start at first point

    for(int i = 0; i < points.length(); i++) {
        path.lineTo(points[i]);

        if(i > 0)
            squarePath.lineTo(points[i].x(), points[i - 1].y());
        squarePath.lineTo(points[i]);
    }

    // close fill polygon
    fillPath = path;
    fillPath.lineTo(points.last().x(), graphSize.height());
    fillPath.lineTo(points.first().x(), graphSize.height());
    fillPath.lineTo(points.first());

    painter->setPen(QPen(options.color, options.lineWidth));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->drawPath(path);
    painter->fillPath(fillPath, QBrush(QColor(
                                           options.color.red(),
                                           options.color.green(),
                                           options.color.blue(),
                                           50)));
    if(!options.drawSquareLine)
        return;

    // draw square line
    QPen pen(options.squareLineColor);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawPath(squarePath);
}
