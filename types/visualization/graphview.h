#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QQuickPaintedItem>
#include "graphcontent.h"
#include "../../core/painteditem.h"

class GraphView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(GraphContent* graph READ graph WRITE setGraph NOTIFY graphChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

    private:
        GraphContent* m_graph;
        QColor m_lineColor;
        int m_lineWidth;

    public:
        GraphView();

        virtual void paint(QPainter *painter);

        GraphContent* graph() const;
        QColor lineColor() const;
        int lineWidth() const;

    public slots:
        void setGraph(GraphContent* graph);
        void setLineColor(QColor lineColor);
        void setLineWidth(int lineWidth);

    signals:
        void graphChanged(GraphContent* graph);
        void lineColorChanged(QColor lineColor);
        void lineWidthChanged(int lineWidth);
};



#endif // GRAPHVIEW_H
