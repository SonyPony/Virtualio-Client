#ifndef GraphAxis_H
#define GraphAxis_H

#include "abstractgraphaxis.h"

class GraphAxis : public AbstractGraphAxis
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QString font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
        Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

    private:
        QString m_font;
        QColor m_textColor;
        QColor m_color;
        int m_lineWidth;
        int m_fontSize;

        void paintHorizontalAxis(QPainter *painter);
        void paintVerticalAxis(QPainter *painter);

    public:
        GraphAxis();

        virtual void paint(QPainter *painter);

        QString font() const;
        QColor textColor() const;
        QColor color() const;
        int lineWidth() const;
        int fontSize() const;

    public slots:
        void setFont(QString font);
        void setTextColor(QColor textColor);
        void setColor(QColor color);
        void setLineWidth(int lineWidth);
        void setFontSize(int fontSize);

    signals:
        void fontChanged(QString font);
        void textColorChanged(QColor textColor);
        void colorChanged(QColor color);
        void lineWidthChanged(int lineWidth);
        void fontSizeChanged(int fontSize);
};

#endif // GraphAxis_H
