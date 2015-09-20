#ifndef ABSTRACTGRAPHAXIS_H
#define ABSTRACTGRAPHAXIS_H

#include <QPainter>
#include <QQuickPaintedItem>
#include <QStringList>
#include "resizeableitem.h"
#include "interval.h"

class AbstractGraphAxis : public ResizeAbleItem
{
        Q_OBJECT
        Q_ENUMS(Direction)
        Q_PROPERTY(Interval* values READ values WRITE setValues NOTIFY valuesChanged)
        Q_PROPERTY(int valuesCount READ valuesCount WRITE setValuesCount NOTIFY valuesCountChanged)
        Q_PROPERTY(double ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

    protected:
        Interval* m_values;
        int m_valuesCount;
        QStringList m_labels;
        double *m_ratio;

        static int calculateValuesCount(double ratio, double valuesCount);


    public:
        AbstractGraphAxis();
        ~AbstractGraphAxis();

        virtual void paint(QPainter *painter) = 0;

        Interval* values() const;
        int valuesCount() const;
        double ratio() const;

    private slots:
        void resizeAxis(double ratio);
        void resizeAxis();

    public slots:
        virtual void setVerticalRatio(double verticalRatio);
        void setValues(Interval* values);
        void setValuesCount(int valuesCount);
        void setRatio(double ratio);

    signals:
        void valuesChanged(Interval* values);
        void valuesCountChanged(int valuesCount);
        void ratioChanged(double ratio);
};

#endif // ABSTRACTGRAPHAXIS_H
