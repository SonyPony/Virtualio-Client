#include "intervaltests.h"
#include "interval.h"

void Tests::IntervalTests::testIsIn()
{
    Interval i(-5, 7);

    QVERIFY(i.isIn(5.4));
    QVERIFY(i.isIn(-5));
    QVERIFY(i.isIn(7));
    QVERIFY(!i.isIn(8.5));
    QVERIFY(!i.isIn(-6));

    QVERIFY(Interval::isIn(-5, 7, 5.4));
    QVERIFY(Interval::isIn(-5, 7, -5));
    QVERIFY(Interval::isIn(-5, 7, 7));
    QVERIFY(!Interval::isIn(-5, 7, 8.5));
    QVERIFY(!Interval::isIn(-5, 7, -6));
}

void Tests::IntervalTests::testLength()
{
    Interval i(-5, 7);

    QCOMPARE(i.length(), 12.);

    i.setMin(2);
    QCOMPARE(i.length(), 5.);
}

void Tests::IntervalTests::testCompare()
{
    Interval i(-5, 7);
    Interval i2(-5, 9);

    QVERIFY(!(i == i2));

    i2.setMax(7);
    QVERIFY(i == i2);
}

void Tests::IntervalTests::testDisjunction()
{
    Interval i(-6, 7);
    Interval i2(-5, 9);
    Interval* result = i & i2;

    QVERIFY(*result == Interval(-6, 9));
}

void Tests::IntervalTests::testCopy()
{
    Interval i(-6, 7);
    Interval i2(-5, 9);

    i = i2;

    QVERIFY(i == i2);
}

void Tests::IntervalTests::testValuePos()
{
    Interval i(-7, 7);

    QVERIFY(i.valuePos(0) == 0.5);
    QVERIFY(i.valuePos(-7) == 0);
    QVERIFY(i.valuePos(7) == 1);
    QVERIFY(i.valuePos(-55) == 0);
    QVERIFY(i.valuePos(55) == 1);
}

void Tests::IntervalTests::testValuePosToValue()
{
    Interval i(-7, 7);

    QVERIFY(i.valuePosToValue(0.5) == 0);
    QVERIFY(i.valuePosToValue(0) == -7);
    QVERIFY(i.valuePosToValue(1) == 7);
}
