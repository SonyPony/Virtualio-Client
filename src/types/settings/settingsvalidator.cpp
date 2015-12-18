#include "settingsvalidator.h"
#include <QStringList>
#include <QJsonArray>
#include <QJsonValue>
#include <QPair>
#include <QDebug>
#include <QString>

QString SettingsValidator::type(QJsonValue::Type jsonType) const
{
    switch (jsonType) {
        case QJsonValue::Null:
            return QStringLiteral("null");

        case QJsonValue::Bool:
            return QStringLiteral("bool");

        case QJsonValue::Double:
            return QStringLiteral("double");

        case QJsonValue::String:
            return QStringLiteral("string");

        case QJsonValue::Array:
            return QStringLiteral("array");

        case QJsonValue::Object:
            return QStringLiteral("object");
        default:
            return QStringLiteral("");
    }
}

QString SettingsValidator::checkKeys(QStringList expectedKeys, QJsonObject object)
{
    for(const QString key: object.keys()) {
        if(expectedKeys.contains(key))
            expectedKeys.removeAll(key);
    }

    if(expectedKeys.length()) {
        QString errorMsg = QString("Expected %1 keys").arg(expectedKeys.join(", "));
        Q_EMIT error(errorMsg);
        return errorMsg;
    }

    return QStringLiteral("");
}

QString SettingsValidator::checkValues(QMap<QString, QJsonValue::Type> pairs, QJsonObject object)
{
    for(const QString key: pairs.keys()) {
        if(object[key].type() != pairs[key]) {
            const QString errorMsg = QString("At key %1 expected value type %2 intead of %3")
                    .arg(key)
                    .arg(this->type(pairs[key]))
                    .arg(this->type(object[key].type()));
            Q_EMIT error(errorMsg);
            return errorMsg;
        }
    }

    return QStringLiteral("");
}

QString SettingsValidator::checkObject(QMap<QString, QJsonValue::Type> objectStructure, QJsonObject object)
{
    QString checkKeysResult = this->checkKeys(objectStructure.keys(), object);

    if(!checkKeysResult.isEmpty())
        return checkKeysResult;

    return this->checkValues(objectStructure, object);
}

QString SettingsValidator::checkEnum(QJsonValue value, QList<double> enumeration)
{
    if(value.type() != QJsonValue::Double)
        return QStringLiteral("Unsupported enum type");

    if(!enumeration.contains(value.toDouble()))
        return QString("Value %1 is not in enumaration (%2)")
                .arg(value.toDouble())
                .arg([&enumeration]() -> QString {      //join double list to QString
                         QString result = "";
                         for(double v: enumeration) {
                             result.append(QString::number(v));
                             result.append(", ");
                         }

                         return result;
                     }());

    return QStringLiteral("");
}

QString SettingsValidator::checkEnum(QJsonValue value, QList<QString> enumeration)
{
    if(value.type() != QJsonValue::String)
        return QStringLiteral("Unsupported enum type");

    if(!enumeration.contains(value.toString()))
        return QString("Value %1 is not in enumaration (%2)")
                .arg(value.toString())
                .arg(enumeration.join(", "));

    return QStringLiteral("");
}

SettingsValidator::SettingsValidator(QObject *parent) : QObject(parent)
{

}

QString SettingsValidator::checkComboBox(QJsonObject object)
{
    QMap<QString, QJsonValue::Type> expectedValueTypes = {
        { QStringLiteral("values"), QJsonValue::Array }
    };

    return this->checkObject(expectedValueTypes, object);
}

QString SettingsValidator::checkRootObject(QJsonObject object)
{
    QMap<QString, QJsonValue::Type> expectedValueTypes = {
        { QStringLiteral("name"), QJsonValue::String },
        { QStringLiteral("tagStyle"), QJsonValue::Object },
        { QStringLiteral("tagOptions"), QJsonValue::Array },
        { QStringLiteral("moduleSettings"), QJsonValue::Object },
    };

    return this->checkObject(expectedValueTypes, object);
}

QString SettingsValidator::checkTagStyle(QJsonObject object)
{
    QMap<QString, QJsonValue::Type> expectedValueTypes = {
        { QStringLiteral("primaryColor"), QJsonValue::String },
        { QStringLiteral("secondaryColor"), QJsonValue::String }
    };

    return this->checkValues(expectedValueTypes, object);
}

QString SettingsValidator::checkTagOptions(QJsonObject object)
{

}

QString SettingsValidator::checkModuleSettings(QJsonObject object)
{

}

