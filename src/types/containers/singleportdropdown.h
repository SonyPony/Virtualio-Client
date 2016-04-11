#ifndef SINGLEPORTDROPDOWN_H
#define SINGLEPORTDROPDOWN_H

#include <QQuickItem>
#include "dropdown.h"
#include <QSvgRenderer>
#include <QPropertyAnimation>
#include <types/visualization/bytedatapanel.h>

class SinglePortDropDown : public DropDown
{
        Q_OBJECT
        Q_PROPERTY(QColor notificationColor READ notificationColor WRITE setNotificationColor NOTIFY notificationColorChanged)
        Q_PROPERTY(QStringList dataColors READ dataColors WRITE setDataColors NOTIFY dataColorsChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
        Q_PROPERTY(int dataPanelHeight READ dataPanelHeight WRITE setDataPanelHeight NOTIFY dataPanelHeightChanged)

    private:
        QPropertyAnimation* m_blinkAnimation;
        QSvgRenderer* m_arrowRenderer;
        QStringList m_dataColors;
        QColor m_lineColor;
        int m_margin;
        QColor m_originTitleColor;
        int m_dataPanelHeight;
        QColor m_notificationColor;
        bool m_blinking;

    protected:
        virtual void mousePressEvent(QMouseEvent* e);

    public:
        SinglePortDropDown(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QStringList dataColors() const;
        QColor lineColor() const;
        int margin() const;
        int dataPanelHeight() const;
        bool hidden() const;
        QColor notificationColor() const;

    public Q_SLOTS:
        void startBlink();
        void stopBlink();
        void addMessage(int data, int usTime);

        void setDataColors(QStringList dataColors);
        void setLineColor(QColor lineColor);
        void setMargin(int margin);
        void setDataPanelHeight(int dataPanelHeight);
        void setNotificationColor(QColor notificationColor);

    Q_SIGNALS:
        void dataColorsChanged(QStringList dataColors);
        void lineColorChanged(QColor lineColor);
        void marginChanged(int margin);
        void dataPanelHeightChanged(int dataPanelHeight);
        void notificationColorChanged(QColor notificationColor);
};

#endif // SINGLEPORTDROPDOWN_H
