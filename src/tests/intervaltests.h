#ifndef INTERVALTESTS_H
#define INTERVALTESTS_H

#include <QObject>
#include <QTest>

namespace Tests {
    class IntervalTests : public QObject
    {
            Q_OBJECT

        private Q_SLOTS:
            void testIsIn();
            void testLength();
            void testCompare();
            void testDisjunction();
            void testCopy();
            void testValuePos();
    };
}
#endif // INTERVALTESTS_H
