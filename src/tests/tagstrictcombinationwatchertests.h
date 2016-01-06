#ifndef TAGSTRICTCOMBINATIONWATCHERTESTS_H
#define TAGSTRICTCOMBINATIONWATCHERTESTS_H

#include <QObject>
#include <QTest>

namespace Tests {
    class TagStrictCombinationWatcherTests : public QObject
    {
            Q_OBJECT
        public:
            TagStrictCombinationWatcherTests(QObject *parent = 0);

        private Q_SLOTS:
            void checkChecking();
    };
}
#endif // TAGSTRICTCOMBINATIONWATCHERTESTS_H
