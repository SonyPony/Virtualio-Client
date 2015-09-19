#ifndef FRACTION_H
#define FRACTION_H


class Fraction
{
    private:
        double m_denominator;
        double m_numerator;

    public:
        Fraction(double numerator, double denominator);

        double operator *(double other);
        double operator /(double other);

        double value();
};

#endif // FRACTION_H
