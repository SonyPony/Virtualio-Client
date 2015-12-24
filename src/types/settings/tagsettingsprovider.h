#ifndef TAGSETTINGSPROVIDER_H
#define TAGSETTINGSPROVIDER_H

#include <QObject>
#include "settingsprovider.h"

class TagSettingsProvider : public SettingsProvider
{
        Q_OBJECT
    public:
        TagSettingsProvider(QDir &dir, QObject *parent = 0);
        TagSettingsProvider(QObject *parent = 0);

        QJsonValue tagStyle(const QString settingsName) const;
        QJsonValue tagOptions(const QString settingsName) const;
        QJsonValue moduleSettings(const QString settingsName) const;
};

#endif // TAGSETTINGSPROVIDER_H
