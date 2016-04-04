#ifndef CONSOLEDIALOG_H
#define CONSOLEDIALOG_H

#include <QQuickItem>
#include <types/containers/dropdown.h>
#include <types/containers/singleportdropdown.h>
#include <QSvgRenderer>

class ConsoleDialog : public DropDown
{
        Q_OBJECT
        Q_PROPERTY(int dataPanelHeight READ dataPanelHeight WRITE setDataPanelHeight NOTIFY dataPanelHeightChanged)
        Q_PROPERTY(QStringList portsNames READ portsNames WRITE setPortsNames NOTIFY portsNamesChanged)
        Q_PROPERTY(QQuickItem* flickable READ flickable WRITE setFlickable NOTIFY flickableChanged)
        Q_PROPERTY(QStringList dataColors READ dataColors WRITE setDataColors NOTIFY dataColorsChanged)
        Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
        Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
        Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
        Q_PROPERTY(QColor dropDownsTitleTextColor READ dropDownsTitleTextColor WRITE setDropDownsTitleTextColor NOTIFY dropDownsTitleTextColorChanged)
        Q_PROPERTY(QColor dropDownsTitleColor READ dropDownsTitleColor WRITE setDropDownsTitleColor NOTIFY dropDownsTitleColorChanged)
        Q_PROPERTY(QFont dropDownsTitleFont READ dropDownsTitleFont WRITE setDropDownsTitleFont NOTIFY dropDownsTitleFontChanged)
        Q_PROPERTY(int dropDownsTitleHeight READ dropDownsTitleHeight WRITE setDropDownsTitleHeight NOTIFY dropDownsTitleHeightChanged)

    private:
        QStringList m_portsNames;
        QMap<QString, SinglePortDropDown*> m_ports;
        QQuickItem* m_flickable;
        QStringList m_dataColors;
        QColor m_lineColor;
        int m_time;
        int m_margin;
        QColor m_dropDownsTitleColor;
        QFont m_dropDownsTitleFont;
        int m_dataPanelHeight;
        int m_dropDownsTitleHeight;
        QColor m_dropDownsTitleTextColor;
        QSvgRenderer* m_iconRenderer;

    public:
        ConsoleDialog(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QStringList portsNames() const;
        QQuickItem* flickable() const;
        QStringList dataColors() const;
        QColor lineColor() const;
        int time() const;
        int margin() const;
        QColor dropDownsTitleColor() const;
        QFont dropDownsTitleFont() const;
        int dataPanelHeight() const;
        int dropDownsTitleHeight() const;
        QColor dropDownsTitleTextColor() const;

    private Q_SLOTS:
        void generateDropDowns();

    public Q_SLOTS:
        QQuickItem* container();
        void addMessage(QString potName, int data, int usTime);

        void setPortsNames(QStringList portsNames);
        void setFlickable(QQuickItem* flickable);
        void setDataColors(QStringList dataColors);
        void setLineColor(QColor lineColor);
        void setTime(int time);
        void setMargin(int margin);
        void setDropDownsTitleColor(QColor dropDownsTitleColor);
        void setDropDownsTitleFont(QFont dropDownsTitleFont);
        void setDataPanelHeight(int dataPanelHeight);
        void setDropDownsTitleHeight(int dropDownsTitleHeight);
        void setDropDownsTitleTextColor(QColor dropDownsTitleTextColor);

    Q_SIGNALS:
        void portsNamesChanged(QStringList portsNames);
        void flickableChanged(QQuickItem* flickable);
        void dataColorsChanged(QStringList dataColors);
        void lineColorChanged(QColor lineColor);
        void timeChanged(int time);
        void marginChanged(int margin);
        void dropDownsTitleColorChanged(QColor dropDownsTitleColor);
        void dropDownsTitleFontChanged(QFont dropDownsTitleFont);
        void dataPanelHeightChanged(int dataPanelHeight);
        void dropDownsTitleHeightChanged(int dropDownsTitleHeight);
        void dropDownsTitleTextColorChanged(QColor dropDownsTitleTextColor);
};

#endif // CONSOLEDIALOG_H
