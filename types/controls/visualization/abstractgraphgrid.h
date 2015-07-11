#ifndef ABSTRACTGRAPHGRID_H
#define ABSTRACTGRAPHGRID_H

#include "../resizeableitem.h"
#include <QStringList>
#include "core/interval.h"

class AbstractGraphGrid : public ResizeAbleItem
{
        Q_OBJECT
        Q_PROPERTY(Interval* xAxis READ xAxis WRITE setXAxis NOTIFY xAxisChanged)
        Q_PROPERTY(Interval* yAxis READ yAxis WRITE setYAxis NOTIFY yAxisChanged)
        Q_PROPERTY(int xAxisCount READ xAxisCount WRITE setXAxisCount NOTIFY xAxisCountChanged)
        Q_PROPERTY(int yAxisCount READ yAxisCount WRITE setYAxisCount NOTIFY yAxisCountChanged)
        Q_PROPERTY(qreal ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

    protected:
        qreal m_ratio;
        Interval* m_xAxis;
        Interval* m_yAxis;
        int m_xAxisCount;
        int m_yAxisCount;
        QStringList m_xAxisLabels;
        QStringList m_yAxisLabels;

    public:
        AbstractGraphGrid();

        virtual void paint(QPainter*) = 0;

        Interval* xAxis() const;
        Interval* yAxis() const;
        int xAxisCount() const;
        int yAxisCount() const;
        qreal ratio() const;

    public slots:
        void setXAxis(Interval* xAxis);
        void setYAxis(Interval* yAxis);
        void setXAxisCount(int xAxisCount);
        void setYAxisCount(int yAxisCount);
        void setRatio(qreal ratio);

    signals:
        void xAxisChanged(Interval* xAxis);
        void yAxisChanged(Interval* yAxis);
        void xAxisCountChanged(int xAxisCount);
        void yAxisCountChanged(int yAxisCount);
        void ratioChanged(qreal ratio);
};

#endif // ABSTRACTGRAPHGRID_H
