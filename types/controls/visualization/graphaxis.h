#ifndef GraphAxis_H
#define GraphAxis_H

#include "abstractgraphaxis.h"
#include <functional>

struct GraphPaintProperties{
    int count;
    double piece;
    std::function<QLineF(int)> calculateLinePos;
    std::function<QPointF(int)> calculateTextPos;
    std::function<QString(int)> getText;
};

class GraphAxis : public AbstractGraphAxis
{
        Q_OBJECT
        Q_ENUMS(PaintModes)
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QString font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
        Q_PROPERTY(int offset READ offset NOTIFY offsetChanged)
        Q_PROPERTY(int textMode READ textMode WRITE setTextMode NOTIFY textModeChanged)
        Q_PROPERTY(int gridMode READ gridMode WRITE setGridMode NOTIFY gridModeChanged)

    private:
        QString m_font;
        QColor m_textColor;
        QColor m_color;
        int m_lineWidth;
        int m_fontSize;
        int m_offset;
        GraphPaintProperties m_graphPaintProperties;
        int m_textMode;
        int m_gridMode;

    public:
        GraphAxis();
        ~GraphAxis();

        enum PaintModes {
            ExcludeOdd,
            ExcludeEven,
            ExcludeFirst,
            ExcludeLast,
            ExcludeFirstAndLast,
            ExcludeNone
        };

        virtual void paint(QPainter *painter);
        virtual void wheelEvent(QWheelEvent *e);

        QPoint calculatePointPos(double value);

        QString font() const;
        QColor textColor() const;
        QColor color() const;
        int lineWidth() const;
        int fontSize() const;
        int offset() const;
        GraphPaintProperties graphPaintProperties() const;
        int textMode() const;
        int gridMode() const;

    private slots:
        void calculateOffset();
        void setRatioBinding(int direction);

    public slots:
        void setFont(QString font);
        void setTextColor(QColor textColor);
        void setColor(QColor color);
        void setLineWidth(int lineWidth);
        void setFontSize(int fontSize);
        void setTextMode(int textMode);
        void setGridMode(int gridMode);

    signals:
        void fontChanged(QString font);
        void textColorChanged(QColor textColor);
        void colorChanged(QColor color);
        void lineWidthChanged(int lineWidth);
        void fontSizeChanged(int fontSize);
        void offsetChanged(int);
        void propertiesReady();
        void textModeChanged(int textMode);
        void gridModeChanged(int gridMode);
};

#endif // GraphAxis_H
