#include "settingsimporter.h"
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>
#include <QDebug>

SettingsImporter::SettingsImporter(QDir &dir, QObject *parent) : QObject(parent), m_dir(dir)
{}

QStringList SettingsImporter::loadRawData()
{
    QStringList rawData;
    QFileInfo fileInfo;
    QFile file;

    for(QString filename: m_dir.entryList(QDir::Files)) {
        fileInfo.setFile(filename);
        if(fileInfo.completeSuffix() == QStringLiteral("json")) {
            file.setFileName(m_dir.absoluteFilePath(filename));
            if(file.open(QIODevice::ReadOnly)) {
                rawData.append(file.readAll());
                file.close();
            }
        }
    }

    return rawData;
}

QJsonArray SettingsImporter::parse(QStringList rawData)
{
    QJsonArray settings;

    for(QString jsonRaw: rawData)
        settings.append(QJsonDocument::fromJson(jsonRaw.toUtf8()).object());

    for(QJsonValue v: settings) {
        for(QJsonValue vv: v.toObject())
            qDebug() << vv;
    }

    return settings;
}

