#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}

Interval *Core::interval()
{
    Interval *buffer = new Interval;
    return buffer;
}

Interval *Core::interval(double min, double max)
{
    Interval *buffer = new Interval(min, max);
    return buffer;
}
