#ifndef SETTINGSIMPORTER_H
#define SETTINGSIMPORTER_H

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QJsonObject>
#include "../tests/settingsimportertests.h"

class SettingsImporter : public QObject
{
        Q_OBJECT
    friend class Tests::SettingsImporterTests;

    protected:
        QDir m_dir;

        QStringList loadRawData();
        QJsonArray parse(QStringList rawData);

    public:
        SettingsImporter(QDir& dir, QObject *parent = 0);

        QJsonArray loadSettings();
};

#endif // SETTINGSIMPORTER_H
