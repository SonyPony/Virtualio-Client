#include "interval.h"

Interval::Interval(QObject *parent): QObject(parent)
{
    m_min = 0;
    m_max = 0;
}

Interval::Interval(double min, double max)
{
    m_min = min;
    m_max = max;
}

bool Interval::isIn(double min, double max, double value)
{
    if(value >= min && value <= max)
        return true;
    return false;
}

double Interval::length()
{
    return qAbs(m_max  - m_min);
}

bool Interval::isIn(double value)
{
    if(value >= m_min && value <= m_max)
        return true;
    return false;
}

double Interval::valuePos(double value)
{
    if(!isIn(value))
        return -1.;

    return 1. / (length() / (value - m_min));
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
    Interval *buffer = new Interval(qMin(this->min(), r.min()), qMax(this->max(), r.max()));
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

