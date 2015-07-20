#ifndef GraphAxis_H
#define GraphAxis_H

#include "abstractgraphaxis.h"
#include <functional>

class GraphAxis : public AbstractGraphAxis
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QString font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
        Q_PROPERTY(int offset READ offset NOTIFY offsetChanged)
        Q_PROPERTY(double ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

    private:
        QString m_font;
        QColor m_textColor;
        QColor m_color;
        int m_lineWidth;
        int m_fontSize;
        int m_offset;
        double *m_ratio;

        struct GraphPaintProperties{
            int count;
            double piece;
            std::function<QLineF(int)> calculateLinePos;
            std::function<QPointF(int)> calculateTextPos;
            std::function<QString(int)> getText;
        };

    public:
        GraphAxis();
        ~GraphAxis();

        virtual void paint(QPainter *painter);
        virtual void wheelEvent(QWheelEvent *e);

        QString font() const;
        QColor textColor() const;
        QColor color() const;
        int lineWidth() const;
        int fontSize() const;
        int offset() const;
        double ratio() const;

    private slots:
        void calculateOffset();
        void setRatioBinding(int direction);

    public slots:
        void setFont(QString font);
        void setTextColor(QColor textColor);
        void setColor(QColor color);
        void setLineWidth(int lineWidth);
        void setFontSize(int fontSize);
        void setRatio(double ratio);

    signals:
        void fontChanged(QString font);
        void textColorChanged(QColor textColor);
        void colorChanged(QColor color);
        void lineWidthChanged(int lineWidth);
        void fontSizeChanged(int fontSize);
        void ratioChanged(double ratio);
        void offsetChanged(int);
};

#endif // GraphAxis_H
