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
        QJsonValue m_settings;

    public:
        SettingsProvider(QDir &dir, QObject *parent = 0);

        QJsonArray settings() const;

    signals:

    public slots:
};

#endif // SETTINGSPROVIDER_H
