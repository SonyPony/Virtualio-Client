#include "graphicallogic.h"


QPointF GraphicalLogic::centerPoint(double x, double y, double width, double height)
{
    return QPointF(x + width / 2., y + height / 2);
}

QPointF GraphicalLogic::centerPoint(QPointF topLeft, QSizeF size)
{
    return QPointF(topLeft.x() + size.width() / 2.,
                   topLeft.y() + size.height() / 2.);
}

QPointF GraphicalLogic::centerPoint(QQuickItem *object)
{
    return QPointF(object->x() + object->width() / 2.,
                   object->y() + object->height() / 2.);
}

QPointF GraphicalLogic::relativeCenterPoint(double width, double height)
{
    return QPointF(width / 2., height / 2.);
}

QPointF GraphicalLogic::relativeCenterPoint(QSizeF size)
{
    return QPointF((size / 2.).width(), (size / 2.).height());
}

QPointF GraphicalLogic::relativeCenterPoint(QQuickItem *object)
{
    return QPointF(object->width() / 2., object->height() / 2.);
}
