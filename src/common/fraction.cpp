#include "fraction.h"

Fraction::Fraction(double numerator, double denominator)
{
    if(denominator == 0.)
        throw std::logic_error("Division by zero");

    m_numerator = numerator;
    m_denominator = denominator;
}

double Fraction::operator *(double other)
{
    return value() * other;
}

double Fraction::operator /(double other)
{
    if(other == 0.)
        throw std::logic_error("Division by zero");

    return value() / other;
}

double Fraction::value()
{
    return m_numerator / m_denominator;
}

