#include "fraction.h"

Fraction::Fraction(double numerator, double denominator)
{
    m_numerator = numerator;
    m_denominator = denominator;
}

double Fraction::operator *(double other)
{
    return value() * other;
}

double Fraction::operator /(double other)
{
    return value() / other;
}

double Fraction::value()
{
    return m_numerator / m_denominator;
}

