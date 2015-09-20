#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include <QQuickItem>
#include "core/interval.h"

class AbstractGraph : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(Interval* xAxis READ xAxis WRITE setXAxis NOTIFY xAxisChanged)
        Q_PROPERTY(Interval* yAxis READ yAxis WRITE setYAxis NOTIFY yAxisChanged)
        Q_PROPERTY(int xAxisStep READ xAxisStep WRITE setXAxisStep NOTIFY xAxisStepChanged)
        Q_PROPERTY(int yAxisStep READ yAxisStep WRITE setYAxisStep NOTIFY yAxisStepChanged)

    private:
        Interval* m_xAxis;
        Interval* m_yAxis;
        int m_xAxisStep;
        int m_yAxisStep;

    public:
        AbstractGraph();

        Interval* xAxis() const;
        Interval* yAxis() const;
        int xAxisStep() const;
        int yAxisStep() const;

    public slots:
        void setXAxis(Interval* xAxis);
        void setYAxis(Interval* yAxis);
        void setXAxisStep(int xAxisStep);
        void setYAxisStep(int yAxisStep);

    signals:
        void xAxisChanged(Interval* xAxis);
        void yAxisChanged(Interval* yAxis);
        void xAxisStepChanged(int xAxisStep);
        void yAxisStepChanged(int yAxisStep);
};

#endif // ABSTRACTGRAPH_H
