#ifndef COMPOSEABLEDIALOG_H
#define COMPOSEABLEDIALOG_H

#include "painteditem.h"
#include <QPainter>
#include <QJsonArray>
#include "../qmlbridge/core/dynamiccomponentfactory.h"
//#include "../settings/settingsimporter.h"
#include "../settings/tagsettingsprovider.h"

class ComposeableDialog : public PaintedItem
{
        Q_OBJECT
        Q_ENUMS(Panels)
        Q_PROPERTY(QString dirPath READ dirPath WRITE setDirPath NOTIFY dirPathChanged)
        Q_PROPERTY(double panelHeight READ panelHeight WRITE setPanelHeight NOTIFY panelHeightChanged)
        Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)

    protected:
        DynamicComponentFactory* m_componentFactory;
        TagSettingsProvider* m_settingsProvider;
        QString m_dirPath;
        double m_panelHeight;
        QMap<QString, QList<QQuickItem*> > m_components;
        QString m_mode;

        static QQmlEngine* s_qmlEngine;

    public:
        enum Panels { ComboBox, LineEdit, Slider, RadioButtons, CheckBox };

        ComposeableDialog(QQuickItem *parent = 0);

        virtual void paint(QPainter* painter);

        static void setEngine(QQmlEngine* engine);

        QString dirPath() const;
        double panelHeight() const;
        QString mode() const;

        Q_INVOKABLE QVariantMap dialogOptions() const;

    private Q_SLOTS:
        void reloadSettings(QString dirPath);

    public Q_SLOTS:
        void createDialogComponents();
        void setDirPath(QString dirPath);
        void setPanelHeight(double panelHeight);
        void setMode(QString mode);

    Q_SIGNALS:
        void dirPathChanged(QString dirPath);
        void settingUpdated(QJsonArray settings);
        void panelHeightChanged(double panelHeight);
        void modeChanged(QString mode);
};

#endif // COMPOSEABLEDIALOG_H
