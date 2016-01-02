#include "tagsettingsprovider.h"

TagSettingsProvider::TagSettingsProvider(QDir dir, QObject *parent): SettingsProvider(dir, parent)
{}

TagSettingsProvider::TagSettingsProvider(QObject *parent): SettingsProvider(parent)
{}

QJsonValue TagSettingsProvider::tagStyle(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "tagStyle");
}

QJsonValue TagSettingsProvider::tagOptions(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "tagOptions");
}

QJsonValue TagSettingsProvider::moduleSettings(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "moduleSettings");
}
