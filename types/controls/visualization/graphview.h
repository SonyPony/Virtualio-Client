#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QQuickPaintedItem>
#include "graphcontent.h"

class GraphView : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(GraphContent* graph READ graph WRITE setGraph NOTIFY graphChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

    private:
        GraphContent* m_graph;
        QColor m_lineColor;
        QColor m_color;
        int m_lineWidth;

    public:
        GraphView();

        virtual void paint(QPainter *painter);

        GraphContent* graph() const;
        QColor lineColor() const;
        QColor color() const;
        int lineWidth() const;

    public slots:
        void setGraph(GraphContent* graph);
        void setLineColor(QColor lineColor);
        void setColor(QColor color);
        void setLineWidth(int lineWidth);

    signals:
        void graphChanged(GraphContent* graph);
        void lineColorChanged(QColor lineColor);
        void colorChanged(QColor color);
        void lineWidthChanged(int lineWidth);
};



#endif // GRAPHVIEW_H
