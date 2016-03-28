#include "binaryutilstests.h"
#include "bitarray.h"
#include "binaryutils.h"

void Tests::BinaryUtilsTests::testConversionToBitArray()
{
    QByteArray bytes("a");
    BitArray expectingResult(8, false);
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
    BitArray bits = BinaryUtils::toBitArray(expectingResult);

    QCOMPARE(BinaryUtils::toByteArray(bits), expectingResult);

    expectingResult.append("dfdsf3");
    bits = BinaryUtils::toBitArray(expectingResult);

    QCOMPARE(BinaryUtils::toByteArray(bits), expectingResult);

    bits.clear();
    bits.resize(12);

    // letter "a"
    bits.setBit(1);
    bits.setBit(2);
    bits.setBit(7);

    // 1 part of letter "p"
    bits.setBit(9);
    bits.setBit(10);
    bits.setBit(11);
    QCOMPARE(BinaryUtils::toByteArray(bits), QByteArray("ap"));
}

void Tests::BinaryUtilsTests::testExtractingString()
{
    QByteArray bytes("t3hisismessagetests");
    BitArray bits = BinaryUtils::toBitArray(bytes);

    QCOMPARE(BinaryUtils::extractStringFromBits(14 * 8, 5, bits), QStringLiteral("tests"));
    QCOMPARE(BinaryUtils::extractStringFromBits(7 * 8, 7, bits), QStringLiteral("message"));
    QCOMPARE(BinaryUtils::extractStringFromBits(2 * 8, 3, bits), QStringLiteral("his"));
}

void Tests::BinaryUtilsTests::testExtractingNumber()
{
    QByteArray bytes;
    BitArray bits;

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

void Tests::BinaryUtilsTests::testRightShifting()
{
    BitArray sample(4, false);
    sample.setBit(0);
    sample.setBit(2);

    BitArray expecting(6, false);
    expecting.setBit(2);
    expecting.setBit(4);

    QCOMPARE((sample >> 2), expecting);

    expecting.clear();
    expecting.resize(8);
    expecting.setBit(4);
    expecting.setBit(6);

    QCOMPARE((sample >> 4), expecting);

    QCOMPARE((sample >> 0), sample);
}

void Tests::BinaryUtilsTests::testLeftShifting()
{
    BitArray sample(5, false);
    sample.setBit(2);
    sample.setBit(4);

    BitArray expecting(7, false);
    expecting.setBit(2);
    expecting.setBit(4);

    QCOMPARE((sample << 2), expecting);

    expecting.resize(9);
    sample = BitArray(5, false);
    sample.setBit(2);
    sample.setBit(4);

    QCOMPARE((sample << 4), expecting);

    expecting.resize(5);
    QCOMPARE((sample << 0), expecting);
}

void Tests::BinaryUtilsTests::testCopy()
{
    BitArray expecting(6, false);
    expecting.setBit(2);
    expecting.setBit(4);

    BitArray copied = expecting;

    QCOMPARE(expecting, copied);
}




