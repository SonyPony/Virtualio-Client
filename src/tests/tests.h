#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QDebug>
#include <QTest>
#include <QDir>

#include "intervaltests.h"
#include "fractiontests.h"
#include "settingsimportertests.h"

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

        QDir dir(buildDir);
        dir.cd("settings");
        Tests::SettingsImporterTests setImporterTests(dir);

        return Tests::runTests<QObject*>(
                    &intervalTests,
                    &fractionTests,
                    &setImporterTests);
    }
}

#endif // TESTS_H
