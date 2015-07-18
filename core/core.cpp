#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

Interval *Core::interval()
{
    return new Interval;
}

Interval *Core::interval(double min, double max)
{
    return new Interval(min, max);
}
