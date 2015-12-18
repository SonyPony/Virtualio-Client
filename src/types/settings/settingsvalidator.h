#ifndef SETTINGSVALIDATOR_H
#define SETTINGSVALIDATOR_H

#include <QObject>
#include <QJsonObject>
#include <QPair>

class SettingsValidator : public QObject
{
        Q_OBJECT

    protected:
        QString type(QJsonValue::Type jsonType) const;
        QString checkKeys(QStringList expectedKeys, QJsonObject object);
        QString checkValues(QMap<QString, QJsonValue::Type> pairs, QJsonObject object);
        QString checkObject(QMap<QString, QJsonValue::Type> objectStructure, QJsonObject object);

        QString checkEnum(QJsonValue value, QList<double> enumeration);
        QString checkEnum(QJsonValue value, QList<QString> enumeration);

    public:
        SettingsValidator(QObject *parent = 0);

        QString checkComboBox(QJsonObject object);
        QString checkRootObject(QJsonObject object);
        QString checkTagStyle(QJsonObject object);
        QString checkTagOptions(QJsonObject object);
        QString checkModuleSettings(QJsonObject object);

    Q_SIGNALS:
        void error(const QString& msg);
};

#endif // SETTINGSVALIDATOR_H
