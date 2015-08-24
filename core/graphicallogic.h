#ifndef GRAPHICALLOGIC_H
#define GRAPHICALLOGIC_H

#include <QQuickItem>
#include <QPointF>
#include <QSizeF>

namespace GraphicalLogic
{
    QPointF centerPoint(double x, double y, double width, double height);
    QPointF centerPoint(QPointF topLeft, QSizeF size);
    QPointF centerPoint(QQuickItem* object);

    QPointF relativeCenterPoint(double width, double height);
    QPointF relativeCenterPoint(QSizeF size);
    QPointF relativeCenterPoint(QQuickItem* object);
}

#endif // GRAPHICALLOGIC_H
