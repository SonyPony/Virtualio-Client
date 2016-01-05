#ifndef COMPOSEABLEDIALOG_H
#define COMPOSEABLEDIALOG_H

#include "composeabledialogview.h"
#include "painteditem.h"
#include <QPainter>
#include <QJsonArray>
#include "../qmlbridge/core/dynamiccomponentfactory.h"
#include "../settings/tagsettingsprovider.h"

class ComposeableDialog : public PaintedItem
{
        Q_OBJECT
        Q_ENUMS(Panels)
        Q_PROPERTY(QString dirPath READ dirPath WRITE setDirPath NOTIFY dirPathChanged)
        Q_PROPERTY(double panelHeight READ panelHeight WRITE setPanelHeight NOTIFY panelHeightChanged)
        Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)

    private:
        int enumeratedPanelType(QQuickItem* panel) const;
        const char* panelMainProperty(QQuickItem *panel) const;
        const char* panelMainPropertySetter(QQuickItem *panel) const;
        QString componentType(QQuickItem* panel) const;
        QVariant defaultPanelProperty(QQuickItem* panel) const;

    protected:
        DynamicComponentFactory* m_componentFactory;
        TagSettingsProvider* m_settingsProvider;
        QString m_dirPath;
        double m_panelHeight;
        QMap<QString, ComposeableDialogView*> m_views;
        QMap<QString, QList<QQuickItem*> > m_components;
        QString m_mode;
        QFont m_font;
        QColor m_titleColor;

        static QQmlEngine* s_qmlEngine;

    public:
        enum Panels {
            ComboBox = 1,
            LineEdit = 2,
            Slider = 4,
            RadioButtons = 8,
            CheckBox = 16
        };

        ComposeableDialog(QQuickItem *parent = 0);

        virtual void paint(QPainter* painter);

        static void setEngine(QQmlEngine* engine);

        ComposeableDialogView *newView(QString name);
        QString dirPath() const;
        double panelHeight() const;
        QString mode() const;
        QFont font() const;
        QColor titleColor() const;

        Q_INVOKABLE QVariantMap dialogOptions() const;

    private Q_SLOTS:
        void reloadSettings(QString dirPath);
        void showAndHide();

    public Q_SLOTS:
        void createDialogComponents();
        void setDirPath(QString dirPath);
        void setPanelHeight(double panelHeight);
        void setMode(QString mode);
        void setFont(QFont font);
        void setTitleColor(QColor titleColor);
        void setDialogOptions(QVariantMap options);

    Q_SIGNALS:
        void dirPathChanged(QString dirPath);
        void settingUpdated(QJsonArray settings);
        void panelHeightChanged(double panelHeight);
        void modeChanged(QString mode);
        void fontChanged(QFont font);
        void titleColorChanged(QColor titleColor);
};

#endif // COMPOSEABLEDIALOG_H
