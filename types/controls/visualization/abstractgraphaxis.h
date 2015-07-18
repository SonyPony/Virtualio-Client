#ifndef ABSTRACTGRAPHAXIS_H
#define ABSTRACTGRAPHAXIS_H

#include <QPainter>
#include <QQuickPaintedItem>
#include <QStringList>
#include "../resizeableitem.h"
#include "core/interval.h"

class AbstractGraphAxis : public ResizeAbleItem
{
        Q_OBJECT
        Q_ENUMS(Direction)
        Q_PROPERTY(Interval* values READ values WRITE setvalues NOTIFY valuesChanged)
        Q_PROPERTY(int valuesCount READ valuesCount WRITE setvaluesCount NOTIFY valuesCountChanged)

    protected:
        Interval* m_values;
        int m_valuesCount;
        QStringList m_labels;

        static int calculateValuesCount(double ratio, double valuesCount);


    public:
        AbstractGraphAxis();

        virtual void paint(QPainter *painter) = 0;

        Interval* values() const;
        int valuesCount() const;

    private slots:
        void resizeAxis(double ratio);
        void resizeAxis();

    public slots:
        virtual void setVerticalRatio(double verticalRatio);
        void setvalues(Interval* values);
        void setvaluesCount(int valuesCount);

    signals:
        void valuesChanged(Interval* values);
        void valuesCountChanged(int valuesCount);
};

#endif // ABSTRACTGRAPHAXIS_H
