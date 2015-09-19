#ifndef EXTENTEDMATH_H
#define EXTENTEDMATH_H

#include <QPointF>
#include <QRect>
#include <QLine>

namespace ExtentedMath
{
    double distance(QPointF first, QPointF second);
    bool pointInRect(QPoint point, QRect rect);
    double legOfRightTriangle(double otherLeg, double hypotenuse);
    QLineF rectDiagonal(QRectF rect);
    double lineLength(QLineF line);
}

#endif // EXTENTEDMATH_H
