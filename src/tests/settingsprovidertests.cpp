#include "settingsprovidertests.h"

Tests::SettingsProviderTests::SettingsProviderTests(QDir &dir, QObject *parent): QObject(parent)
{
    m_dir = dir;
}
