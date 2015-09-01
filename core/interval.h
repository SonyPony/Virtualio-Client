#ifndef INTERVAL_H
#define INTERVAL_H

#include <QObject>

class Interval: public QObject
{
        Q_OBJECT
        Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
        Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)

    private:
        double m_max;
        double m_min;

    public:
        explicit Interval(QObject *parent = 0);
        Interval(double min, double max);

        static bool isIn(double min, double max, double value);

        Q_INVOKABLE double length();
        bool isIn(double value);
        double valuePos(double value);  //return value 0-1 according to max and min position
        inline bool operator==(const Interval &r);
        inline void operator=(Interval &other);
        inline Interval* operator&(const Interval &r);

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
