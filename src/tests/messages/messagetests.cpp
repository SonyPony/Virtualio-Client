#include "messagetests.h"

void Tests::MessageTests::testExtractingNumber()
{
    QByteArray data;
    data.append(123);

    Tests::TMessage tm;
    tm.setContent(data);

    QCOMPARE(tm.extractNumberFromBytes(0, 8), 123);
    QCOMPARE(tm.extractNumberFromBytes(4, 4), 11);
    QCOMPARE(tm.extractNumberFromBytes(3, 4), 13);
    QCOMPARE(tm.extractNumberFromBytes(2, 4), 14);

    data.clear();
    data.append(244);
    data.append(123);
    tm.setContent(data);

    QCOMPARE(tm.extractNumberFromBytes(2, 4), 13);
    QCOMPARE(tm.extractNumberFromBytes(5, 9), 286);
}

void Tests::MessageTests::testExtractingString()
{
    Tests::TMessage tm;
    tm.setContent("t3hisismessagetests");

    QCOMPARE(tm.extractStringFromBytes(14 * 8, 5), QStringLiteral("tests"));
    QCOMPARE(tm.extractStringFromBytes(7 * 8, 7), QStringLiteral("message"));
    QCOMPARE(tm.extractStringFromBytes(2 * 8, 3), QStringLiteral("his"));
}

void Tests::MessageTests::testAddingParam()
{
    Tests::TMessage tm;
    tm.setContent("Ahoj");
    int startIndex;

    startIndex = tm.addNumberToContent(123, 8);
    QCOMPARE(tm.extractNumberFromBytes(startIndex, 8), 123);

    startIndex = tm.addNumberToContent(23, 2);
    QCOMPARE(tm.extractNumberFromBytes(startIndex, 2), 3);

    startIndex = tm.addCharToContent('g');
    QCOMPARE(tm.extractStringFromBytes(startIndex, 1), QStringLiteral("g"));
}

void Tests::MessageTests::testGeneratingHeader()
{
    Tests::TMessage tm;
    tm.setContent("ag");

    tm.setType(TMessage::Type::PinsInit);
    QBitArray header(15, false);
    header[4] = true;
    header[10] = true;

    QCOMPARE(tm.generateHeader(), header);

    tm.addNumberToContent(1, 2);
    header[13] = true;

    QCOMPARE(tm.generateHeader(), header);
}
