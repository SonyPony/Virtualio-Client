#include "extentedmath.h"
#include "interval.h"
#include <qmath.h>

double ExtentedMath::distance(QPointF first, QPointF second)
{
    return qSqrt(qPow(first.x() - second.x(), 2.) + qPow(first.y() - second.y(), 2.));
}

bool ExtentedMath::pointInRect(QPoint point, QRect rect)
{
    if(Interval::isIn(rect.x(), rect.x() + rect.width(), point.x()) &&
       Interval::isIn(rect.y(), rect.y() + rect.height(), point.y()))
        return true;
    return false;
}


double ExtentedMath::legOfRightTriangle(double otherLeg, double hypotenuse)
{
    Q_ASSERT(otherLeg < hypotenuse);

    return qSqrt(qPow(hypotenuse, 2) - qPow(otherLeg, 2));
}


QLineF ExtentedMath::rectDiagonal(QRectF rect)
{
    return QLineF(rect.x(), rect.y(), rect.x() + rect.width(), rect.y() + rect.height());
}


double ExtentedMath::lineLength(QLineF line)
{
    return qSqrt(qPow(line.dx(), 2.) + qPow(line.dy(), 2.));
}
