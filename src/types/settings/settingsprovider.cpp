#include "settingsprovider.h"

QJsonValue SettingsProvider::extractSingleSettingsOption(const QString settingsName, const QString optionName) const
{
    QJsonObject singleSettings;

    for(QJsonValue vSingleSettings: m_settings) {
        singleSettings = vSingleSettings.toObject();
        Q_ASSERT_X(singleSettings.keys().contains(optionName), "settings option", "option not found");

        if(settingsName == singleSettings["name"].toString())
            return singleSettings[optionName];
    }

    return QJsonValue();
}

SettingsProvider::SettingsProvider(QObject *parent): QObject(parent)
{
    m_settingsImporter = new SettingsImporter(this);

    connect(this, &SettingsProvider::requestUpdateSettings, this, &SettingsProvider::updateSettings);
}

QJsonArray SettingsProvider::settings() const
{
    return m_settings;
}

QStringList SettingsProvider::extractSettingsNames() const
{
    QStringList result;

    for(QJsonValue vSettings: m_settings)
        result.append(vSettings.toObject()["name"].toString());
    return result;
}

QMap<QString, QString> SettingsProvider::extractSettingsLongNames() const
{
    QMap<QString, QString> result;
    QString settingsName;
    QString settingsLongName;

    for(QJsonValue vSettings: m_settings) {
        settingsName = vSettings.toObject()["name"].toString();
        settingsLongName = vSettings.toObject()["longName"].toString();

        if(!settingsLongName.isEmpty())
            result.insert(settingsName, settingsLongName);
    }

    return result;
}

QJsonObject SettingsProvider::extractSettings(QStringList removingKeys, QJsonObject settings)
{
    QJsonObject result = settings;

    for(QString key: removingKeys)
        result.remove(key);

    return result;
}

SettingsProvider::SettingsProvider(QDir& dir, QObject *parent) : SettingsProvider(parent)
{
    m_settingsImporter->setDir(dir.absolutePath());
    this->updateSettings();
}

void SettingsProvider::setDir(QString dirPath)
{
    m_settingsImporter->setDir(dirPath);
    Q_EMIT this->requestUpdateSettings();
}

void SettingsProvider::updateSettings()
{
    m_settings = m_settingsImporter->loadSettings();
    Q_EMIT this->updated();
}

/*QJsonArray SettingsProvider::settings()
{
    //proccesing
    //separate tag settings from module settings

    return m_settingsImporter->loadSettings();
}
*/

