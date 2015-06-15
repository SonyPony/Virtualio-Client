#ifndef INTERVAL_H
#define INTERVAL_H

#include <QObject>

class Interval: QObject
{
        Q_OBJECT
        Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
        Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)

    private:
        double m_max;
        double m_min;

    public:
        Interval();

        Q_INVOKABLE double length();

        double max() const;
        double min() const;

    public slots:
        void setMax(double max);
        void setMin(double min);

    signals:
        void maxChanged(double max);
        void minChanged(double min);
};

#endif // INTERVAL_H
