#include "interval.h"

Interval::Interval()
{

}

Interval::Interval(double min, double max)
{
    m_min = min;
    m_max = max;
}

double Interval::length()
{
    return qAbs(m_max  - m_min);
}

bool Interval::operator==(const Interval &r)
{
    if(this->min() == r.min() && this->max() == r.max())
        return true;
    return false;
}

void Interval::operator=(Interval &other)
{
    setMin(other.min());
    setMax(other.max());
}

Interval* Interval::operator&(const Interval &r)
{
    Interval *buffer = new Interval(qMax(this->min(), r.min()), qMax(this->max(), r.max()));
    return buffer;
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

