#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QQuickPaintedItem>
#include "graphcontent.h"
#include "painteditem.h"

class GraphView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(GraphContent* graph READ graph WRITE setGraph NOTIFY graphChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)

    private:
        GraphContent* m_graph;
        int m_lineWidth;

    public:
        GraphView(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        GraphContent* graph() const;
        int lineWidth() const;

    public slots:
        void setGraph(GraphContent* graph);
        void setLineWidth(int lineWidth);

    signals:
        void graphChanged(GraphContent* graph);
        void lineWidthChanged(int lineWidth);
};



#endif // GRAPHVIEW_H
