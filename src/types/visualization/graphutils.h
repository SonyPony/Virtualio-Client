#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QSizeF>
#include "graphaxis.h"


namespace GraphUtils {
    struct GraphData {
        QList<double> dataX;
        QList<double> dataY;
    };

    struct GraphOptions {
        QColor color;
        QColor squareLineColor;
        bool drawSquareLine;
        int lineWidth;
    };

    QVector<QPointF> calculatePointsPos(GraphData data, GraphAxis* vAxis, GraphAxis* hAxis);
    void drawGraph(QVector<QPointF> points, QSizeF graphSize, GraphOptions options, QPainter *painter);
}

#endif // GRAPHUTILS_H
