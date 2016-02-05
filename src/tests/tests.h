#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QDebug>
#include <QTest>
#include <QDir>

#include "intervaltests.h"
#include "fractiontests.h"
#include "settingsimportertests.h"
#include "settingsvalidatortests.h"
#include "tagstrictcombinationwatchertests.h"
#include "messages/messagetests.h"

namespace Tests {
    template<typename sT, typename... T>
    int runTests(T... args)
    {
        int result = 0;

        sT a[] = {args...};
        for(sT b: a)
            result |= QTest::qExec(b);
        return result;
    }

    int run(QDir buildDir)
    {
        Tests::FractionTests fractionTests;
        Tests::IntervalTests intervalTests;
        Tests::TagStrictCombinationWatcherTests tcwTests;
        Tests::MessageTests msgTests;

        QDir dir(buildDir);
        dir.cd("src/tests/settingsexamples");

        Tests::SettingsImporterTests setImporterTests(dir);
        Tests::SettingsValidatorTests setValidatorTests(dir);

        return Tests::runTests<QObject*>(
                    &intervalTests,
                    &fractionTests,
                    &setImporterTests,
                    &setValidatorTests,
                    &tcwTests,
                    &msgTests);
    }
}

#endif // TESTS_H
