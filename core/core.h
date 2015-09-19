#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "interval.h"

namespace ExtentedEnums {
    enum Direction { Top, Left, Bottom, Right };
}

class Core : public QObject
{
        Q_OBJECT

    public:
        explicit Core(QObject *parent = 0);

        Q_INVOKABLE Interval *interval();
        Q_INVOKABLE Interval *interval(double min, double max);
};

#endif // CORE_H
