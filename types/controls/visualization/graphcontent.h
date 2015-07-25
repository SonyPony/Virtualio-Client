#ifndef GRAPHCONTENT_H
#define GRAPHCONTENT_H

#include "abstractgraphcontent.h"

class GraphContent : public AbstractGraphContent
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(int contentY READ contentY WRITE setContentY NOTIFY contentYChanged)

    private:
        int m_lineWidth;
        QColor m_color;
        QColor m_fillColor;
        int m_contentY;

        inline QPoint combinePoints(QPoint verAxis, QPoint horAxis);

    public:
        GraphContent();

        virtual void paint(QPainter* painter);

        int lineWidth() const;
        QColor color() const;
        QColor fillColor() const;
        int contentY() const;

    public slots:
        void setLineWidth(int lineWidth);
        void setColor(QColor color);
        void setFillColor(QColor fillColor);
        void setContentY(int contentY);

    signals:
        void lineWidthChanged(int lineWidth);
        void colorChanged(QColor color);
        void fillColorChanged(QColor fillColor);
        void contentYChanged(int contentY);
};

#endif // GRAPHCONTENT_H
