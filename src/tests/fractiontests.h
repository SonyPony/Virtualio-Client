#ifndef FRACTIONTESTS_H
#define FRACTIONTESTS_H

#include <QObject>
#include <QTest>
#include "fraction.h"
#include "tests.h"

namespace Tests {
    class FractionTests : public QObject
    {
            Q_OBJECT
        private Q_SLOTS:
            void testValue();
            void testMultiplication();
            void testDivision();
            void testZeroDivision();
    };
}
#endif // FRACTIONTESTS_H
