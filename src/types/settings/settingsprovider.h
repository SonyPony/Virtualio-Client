#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <QObject>
#include <QDir>
#include <QJsonArray>
#include "settingsimporter.h"

class SettingsProvider : public QObject
{
        Q_OBJECT
    protected:
        SettingsImporter* m_settingsImporter;
        QJsonArray m_settings;

        QJsonValue extractSingleSettingsOption(const QString settingsName, const QString optionName) const;

    public:
        SettingsProvider(QDir &dir, QObject *parent = 0);
        SettingsProvider(QObject *parent = 0);

        QJsonArray settings() const;
        QStringList extractSettingsNames() const;

        static QJsonObject extractSettings(QStringList removingKeys, QJsonObject settings);

    public Q_SLOTS:
        void setDir(QString dirPath);
        void updateSettings();

    Q_SIGNALS:
        void requestUpdateSettings();
        void updated();
};

#endif // SETTINGSPROVIDER_H
