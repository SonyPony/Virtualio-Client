#include "settingsprovider.h"

SettingsProvider::SettingsProvider(QDir& dir, QObject *parent) : QObject(parent)
{
    m_settingsImporter = new SettingsImporter(dir, this);
}

QJsonArray SettingsProvider::settings() const
{
    //proccesing
    return m_settingsImporter->loadSettings();
}


