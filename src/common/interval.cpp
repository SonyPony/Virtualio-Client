#include "interval.h"
#include <QDebug>

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

bool Interval::isIn(double value) const
{
    if(value >= m_min && value <= m_max)
        return true;
    return false;
}

double Interval::valuePos(double value)
{
    if(!isIn(value)) {    // fix zero division
        if(value <= m_min)
            return 0;
        else
            return 1;
    }

    return (value - m_min) / length();
}

double Interval::valuePosToValue(double valuePos)
{
    Q_ASSERT(Interval::isIn(0, 1, valuePos));
    return valuePos * length() + m_min;
}

bool Interval::operator==(Interval const &r)
{
    if(m_min == r.min() && m_max == r.max())
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
    Interval *buffer = new Interval(qMin(m_min, r.min()), qMax(m_max, r.max()));
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

