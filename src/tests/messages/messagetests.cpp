#include "messagetests.h"
#include <QDebug>

void Tests::MessageTests::testExtractingNumber()
{
    QByteArray data;
    data.append(123);

    Tests::TMessage tm;
    tm.setContent(data);
    QCOMPARE(tm.extractNumberFromContent(0, 8), 123);
    QCOMPARE(tm.extractNumberFromContent(4, 4), 11);
    QCOMPARE(tm.extractNumberFromContent(3, 4), 13);
    QCOMPARE(tm.extractNumberFromContent(2, 4), 14);

    data.clear();
    data.append(244);
    data.append(123);
    tm.setContent(data);

    QCOMPARE(tm.extractNumberFromContent(2, 4), 13);
    QCOMPARE(tm.extractNumberFromContent(5, 9), 286);
}

void Tests::MessageTests::testExtractingString()
{
    Tests::TMessage tm;
    tm.setContent("t3hisismessagetests");

    QCOMPARE(tm.extractStringFromContent(14 * 8, 5), QStringLiteral("tests"));
    QCOMPARE(tm.extractStringFromContent(7 * 8, 7), QStringLiteral("message"));
    QCOMPARE(tm.extractStringFromContent(2 * 8, 3), QStringLiteral("his"));
}

void Tests::MessageTests::testAddingParam()
{
    Tests::TMessage tm;
    tm.setContent("Ahoj");
    int startIndex;

    startIndex = tm.addNumberToContent(123, 8);
    QCOMPARE(tm.extractNumberFromContent(startIndex, 8), 123);

    startIndex = tm.addNumberToContent(23, 2);
    QCOMPARE(tm.extractNumberFromContent(startIndex, 2), 3);

    startIndex = tm.addCharToContent('g');
    QCOMPARE(tm.extractStringFromContent(startIndex, 1), QStringLiteral("g"));
}

void Tests::MessageTests::testGeneratingHeader()
{
    /*Tests::TMessage tm;
    tm.setContent("ag");

    tm.setType(TMessage::Type::PinsInit);
    BitArray header(15, false);
    header.setBit(4);
    header.setBit(10);
    qDebug() << "head";
    QCOMPARE(tm.generateHeader(), header);

    tm.addNumberToContent(1, 2);
    header.setBit(13);

    QCOMPARE(tm.generateHeader(), header);*/
}
