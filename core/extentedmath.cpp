#include "extentedmath.h"
#include "interval.h"


double ExtentedMath::distance(QPointF first, QPointF second)
{
    return sqrt(pow(first.x() - second.x(), 2.) + pow(first.y() - second.y(), 2.));
}

bool ExtentedMath::pointInRect(QPoint point, QRect rect)
{
    if(Interval::isIn(rect.x(), rect.x() + rect.width(), point.x()) &&
       Interval::isIn(rect.y(), rect.y() + rect.height(), point.y()))
        return true;
    return false;
}
