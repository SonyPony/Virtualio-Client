#include "tagstrictcombinationwatchertests.h"
#include <types/layout/tagstrictcombinationwatcher.h>

Tests::TagStrictCombinationWatcherTests::TagStrictCombinationWatcherTests(QObject *parent) : QObject(parent)
{
}


void Tests::TagStrictCombinationWatcherTests::checkChecking()
{
    TagStrictCombinationWatcher tcw;

    tcw.addAllowedCombination({"1", "2", "4"});
    tcw.addAllowedCombination({"6", "7", "8"});

    QVERIFY(tcw.checkCombination({"2"}));
    QVERIFY(tcw.checkCombination({"4"}));
    QVERIFY(tcw.checkCombination({"4", "1"}));
    QVERIFY(tcw.checkCombination({"2", "1"}));
    QVERIFY(tcw.checkCombination({"1", "4"}));
    QVERIFY(tcw.checkCombination({"1", "4", "2"}));
    QVERIFY(tcw.checkCombination({"1", "2", "4"}));
    QVERIFY(tcw.checkCombination({"2", "1", "4"}));
    QVERIFY(tcw.checkCombination({"6", "7"}));
    QVERIFY(tcw.checkCombination({"6", "8"}));
    QVERIFY(tcw.checkCombination({"7", "8", "6"}));

    QVERIFY(!tcw.checkCombination({"5", "8"}));
    QVERIFY(!tcw.checkCombination({"3", "1"}));
    QVERIFY(!tcw.checkCombination({"1", "1"}));
    QVERIFY(!tcw.checkCombination({"4", "3"}));
    QVERIFY(!tcw.checkCombination({"3", "2"}));
    QVERIFY(!tcw.checkCombination({"3", "2", "1"}));
    QVERIFY(!tcw.checkCombination({"4", "7", "1"}));
    QVERIFY(!tcw.checkCombination({"3", "6"}));
    QVERIFY(!tcw.checkCombination({"1", "6"}));
    QVERIFY(!tcw.checkCombination({"8", "3"}));
    QVERIFY(!tcw.checkCombination({"6", "2"}));
    QVERIFY(!tcw.checkCombination({"3", "8", "6"}));
    QVERIFY(!tcw.checkCombination({"4", "7", "1"}));
}
