#include "settingsimportertests.h"
#include <QStringList>
#include <QJsonArray>
#include <QDebug>
#include "../types/settings/settingsimporter.h"

Tests::SettingsImporterTests::SettingsImporterTests(QDir &dir, QObject *parent): m_dir(dir)
{
}

void Tests::SettingsImporterTests::testLoadSettings()
{
    SettingsImporter si(m_dir);

    QStringList rawData = si.loadRawData();
    QVERIFY(!rawData.isEmpty());

    QJsonArray jsonObject = si.parse(rawData);
    QVERIFY(!jsonObject.isEmpty());
}
