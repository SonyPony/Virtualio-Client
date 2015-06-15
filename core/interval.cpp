#include "interval.h"

Interval::Interval()
{

}

double Interval::length()
{
    return qAbs(m_max  - m_min);
}

double Interval::max() const
{
    return m_max;
}

double Interval::min() const
{
    return m_min;
}

void Interval::setMax(double max)
{
    if (m_max == max)
        return;

    m_max = max;
    emit maxChanged(max);
}

void Interval::setMin(double min)
{
    if (m_min == min)
        return;

    m_min = min;
    emit minChanged(min);
}

