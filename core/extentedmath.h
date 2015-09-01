#ifndef EXTENTEDMATH_H
#define EXTENTEDMATH_H

#include <QPointF>
#include <QRect>

namespace ExtentedMath
{
    double distance(QPointF first, QPointF second);
    bool pointInRect(QPoint point, QRect rect);
}

#endif // EXTENTEDMATH_H
