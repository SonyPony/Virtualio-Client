#ifndef GRAPHCONTENT_H
#define GRAPHCONTENT_H

#include "abstractgraphcontent.h"
#include "graphutils.h"

class GraphContent : public AbstractGraphContent
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)
        Q_PROPERTY(QColor squareLineColor READ squareLineColor WRITE setSquareLineColor NOTIFY squareLineColorChanged)

    protected:
        int m_lineWidth;
        QColor m_squareLineColor;
        QColor m_color;
        int m_contentY;

    public:
        GraphContent();

        virtual void paint(QPainter* painter);

        //static void drawGraph(QVector<QPointF> points, QSizeF graphSize, GraphOptions options, QPainter *painter);
        //static void drawGraph(GraphData data, GraphAxis* vAxis, GraphAxis* hAxis, GraphOptions options, QPainter* painter);

        int lineWidth() const;
        QColor color() const;
        int contentY() const;
        GraphUtils::GraphData data() const;
        QColor squareLineColor() const;

    public slots:
        void setLineWidth(int lineWidth);
        void setColor(QColor color);
        void setContentY(int contentY);
        void setSquareLineColor(QColor squareLineColor);

    signals:
        void lineWidthChanged(int lineWidth);
        void colorChanged(QColor color);
        void contentYChanged(int contentY);
        void squareLineColorChanged(QColor squareLineColor);
};

#endif // GRAPHCONTENT_H
