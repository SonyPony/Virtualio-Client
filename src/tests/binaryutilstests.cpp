#include "binaryutilstests.h"
#include <QBitArray>
#include "binaryutils.h"

void Tests::BinaryUtilsTests::testConversionToBitArray()
{
    QByteArray bytes("a");
    QBitArray expectingResult(8, false);
    expectingResult.setBit(1);
    expectingResult.setBit(2);
    expectingResult.setBit(7);

    QCOMPARE(BinaryUtils::toBitArray(bytes), expectingResult);

    bytes.append("c");
    expectingResult.resize(16);
    expectingResult.setBit(9);
    expectingResult.setBit(10);
    expectingResult.setBit(15);
    expectingResult.setBit(14);

    QCOMPARE(BinaryUtils::toBitArray(bytes), expectingResult);
}

void Tests::BinaryUtilsTests::testConversionToByteArray()
{
    QByteArray expectingResult("3");
    QBitArray bits = BinaryUtils::toBitArray(expectingResult);

    QCOMPARE(BinaryUtils::toByteArray(bits), expectingResult);

    expectingResult.append("dfdsf3");
    bits = BinaryUtils::toBitArray(expectingResult);

    QCOMPARE(BinaryUtils::toByteArray(bits), expectingResult);
}

void Tests::BinaryUtilsTests::testExtractingString()
{
    QByteArray bytes("t3hisismessagetests");
    QBitArray bits = BinaryUtils::toBitArray(bytes);

    QCOMPARE(BinaryUtils::extractStringFromBits(14 * 8, 5, bits), QStringLiteral("tests"));
    QCOMPARE(BinaryUtils::extractStringFromBits(7 * 8, 7, bits), QStringLiteral("message"));
    QCOMPARE(BinaryUtils::extractStringFromBits(2 * 8, 3, bits), QStringLiteral("his"));
}

void Tests::BinaryUtilsTests::testExtractingNumber()
{
    QByteArray bytes;
    QBitArray bits;

    bytes.append(123);
    bits = BinaryUtils::toBitArray(bytes);

    QCOMPARE(BinaryUtils::extractNumberFromBits(0, 8, bits), 123);
    QCOMPARE(BinaryUtils::extractNumberFromBits(4, 4, bits), 11);
    QCOMPARE(BinaryUtils::extractNumberFromBits(3, 4, bits), 13);
    QCOMPARE(BinaryUtils::extractNumberFromBits(2, 4, bits), 14);

    bytes.clear();
    bytes.append(244);
    bytes.append(123);
    bits = BinaryUtils::toBitArray(bytes);

    QCOMPARE(BinaryUtils::extractNumberFromBits(2, 4, bits), 13);
    QCOMPARE(BinaryUtils::extractNumberFromBits(5, 9, bits), 286);
}
