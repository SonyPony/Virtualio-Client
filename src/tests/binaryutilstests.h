#ifndef TESTBINARYUTILS_H
#define TESTBINARYUTILS_H

#include <QObject>
#include <QTest>

namespace Tests {
    class BinaryUtilsTests : public QObject
    {
            Q_OBJECT
        private Q_SLOTS:
            void testConversionToBitArray();
            void testConversionToByteArray();
            void testExtractingString();
            void testExtractingNumber();
    };
}

#endif // TESTBINARYUTILS_H
