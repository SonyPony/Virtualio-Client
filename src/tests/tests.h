#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QDebug>
#include <QTest>

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
}

#endif // TESTS_H
