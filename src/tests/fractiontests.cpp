#include "fractiontests.h"

void Tests::FractionTests::testValue()
{
    QVERIFY(Fraction(2, 4).value() == 0.5);
    QVERIFY(Fraction(8, 4).value() == 2);
}

void Tests::FractionTests::testMultiplication()
{
    QVERIFY(Fraction(2, 4) * 2. == 1.);
    QVERIFY(Fraction(-2, 2) * 0.5 == -0.5);
}

void Tests::FractionTests::testDivision()
{
    QVERIFY(Fraction(2, 4) / 2. == 0.25);
    QVERIFY(Fraction(-2, 2) / 0.5 == -2);
}

void Tests::FractionTests::testZeroDivision()
{
    QVERIFY_EXCEPTION_THROWN(Fraction(3, 0), std::logic_error);
    QVERIFY_EXCEPTION_THROWN(Fraction(3, 4) / 0, std::logic_error);
}
