#ifndef BYTEDATAPANEL_H
#define BYTEDATAPANEL_H

#include <QQuickItem>
#include "painteditem.h"

class ByteDataPanel : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int data READ data WRITE setData NOTIFY dataChanged)
        Q_PROPERTY(QStringList dataColors READ dataColors WRITE setDataColors NOTIFY dataColorsChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
        Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
        Q_PROPERTY(QFont datasFont READ datasFont WRITE setDatasFont NOTIFY datasFontChanged)

    private:
        int m_data;
        QStringList m_dataColors;
        QColor m_lineColor;
        int m_time;
        int m_margin;
        QFont m_datasFont;

    public:
        ByteDataPanel(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        int data() const;
        QStringList dataColors() const;
        QColor lineColor() const;
        int time() const;
        int margin() const;
        QFont datasFont() const;

    public Q_SLOTS:
        void setData(int data);
        void setDataColors(QStringList dataColors);
        void setLineColor(QColor lineColor);
        void setTime(int time);
        void setMargin(int margin);
        void setDatasFont(QFont datasFont);

    Q_SIGNALS:
        void dataChanged(int data);
        void dataColorsChanged(QStringList dataColors);
        void lineColorChanged(QColor lineColor);
        void timeChanged(int time);
        void marginChanged(int margin);
        void datasFontChanged(QFont datasFont);
};

#endif // BYTEDATAPANEL_H
