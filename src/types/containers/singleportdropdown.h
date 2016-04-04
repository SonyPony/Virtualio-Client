#ifndef SINGLEPORTDROPDOWN_H
#define SINGLEPORTDROPDOWN_H

#include <QQuickItem>
#include "dropdown.h"
#include <QSvgRenderer>
#include <types/visualization/bytedatapanel.h>

class SinglePortDropDown : public DropDown
{
        Q_OBJECT
        Q_PROPERTY(QStringList dataColors READ dataColors WRITE setDataColors NOTIFY dataColorsChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
        Q_PROPERTY(int dataPanelHeight READ dataPanelHeight WRITE setDataPanelHeight NOTIFY dataPanelHeightChanged)

    private:
        QSvgRenderer* m_arrowRenderer;
        QStringList m_dataColors;
        QColor m_lineColor;
        int m_margin;
        int m_dataPanelHeight;

    public:
        SinglePortDropDown(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QStringList dataColors() const;
        QColor lineColor() const;
        int margin() const;
        int dataPanelHeight() const;

    public Q_SLOTS:
        void addMessage(int data, int usTime);

        void setDataColors(QStringList dataColors);
        void setLineColor(QColor lineColor);
        void setMargin(int margin);
        void setDataPanelHeight(int dataPanelHeight);

    Q_SIGNALS:
        void dataColorsChanged(QStringList dataColors);
        void lineColorChanged(QColor lineColor);
        void marginChanged(int margin);
        void dataPanelHeightChanged(int dataPanelHeight);
};

#endif // SINGLEPORTDROPDOWN_H
