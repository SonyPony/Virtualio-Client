#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QDebug>
#include <QTest>

namespace Tests {
    template<typename sT, typename... T>
    int runTests(sT first, T... args)
    {
        int result = 0;

        sT a[] = {first, args...};
        for(sT b: a)
            result |= QTest::qExec(b);
        return result;
    }
}

#endif // TESTS_H
