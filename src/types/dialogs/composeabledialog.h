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
        Q_PROPERTY(QString dirPath READ dirPath WRITE setDirPath NOTIFY dirPathChanged)
        Q_PROPERTY(double panelHeight READ panelHeight WRITE setPanelHeight NOTIFY panelHeightChanged)

    protected:
        DynamicComponentFactory* m_componentFactory;
        TagSettingsProvider* m_settingsProvider;
        QString m_dirPath;
        double m_panelHeight;
        QMap<QString, QList<QQuickItem*> > m_components;

        static QQmlEngine* s_qmlEngine;

    public:
        ComposeableDialog(QQuickItem *parent = 0);

        virtual void paint(QPainter* painter);

        static void setEngine(QQmlEngine* engine);

        QString dirPath() const;
        double panelHeight() const;

    private Q_SLOTS:
        void reloadSettings(QString dirPath);

    public Q_SLOTS:
        void createDialogComponents();
        void setDirPath(QString dirPath);
        void setPanelHeight(double panelHeight);

    Q_SIGNALS:
        void dirPathChanged(QString dirPath);
        void settingUpdated(QJsonArray settings);
        void panelHeightChanged(double panelHeight);
};

#endif // COMPOSEABLEDIALOG_H
