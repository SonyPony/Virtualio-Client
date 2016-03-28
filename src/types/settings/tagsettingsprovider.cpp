#include "tagsettingsprovider.h"

TagSettingsProvider::TagSettingsProvider(QDir dir, QObject *parent): SettingsProvider(dir, parent)
{}

TagSettingsProvider::TagSettingsProvider(QObject *parent): SettingsProvider(parent)
{}

TagSettings TagSettingsProvider::tagSettings(const QString settingsName) const
{
    Q_ASSERT(TagSettingsProvider::extractSettingsNames().contains(settingsName));

    QJsonObject wantedSettings;

    for(QJsonValue vSettings: m_settings) {
        wantedSettings = vSettings.toObject();

        if(wantedSettings["name"] == settingsName) {
            TagSettings result(wantedSettings);
            return result;
        }
    }

    Q_ASSERT(false);
    return TagSettings(QJsonObject());
}

QJsonValue TagSettingsProvider::tagStyle(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "tagStyle");
}

QJsonValue TagSettingsProvider::tagOptions(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "tagOptions");
}

QJsonValue TagSettingsProvider::interactiveControls(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "interactiveControls");
}

QJsonValue TagSettingsProvider::moduleSettings(const QString settingsName) const
{
    return this->extractSingleSettingsOption(settingsName, "moduleSettings");
}
