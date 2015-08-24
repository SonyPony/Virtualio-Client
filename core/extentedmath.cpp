#include "extentedmath.h"



double ExtentedMath::distance(QPointF first, QPointF second)
{
    return sqrt(pow(first.x() - second.x(), 2.) + pow(first.y() - second.y(), 2.));
}
