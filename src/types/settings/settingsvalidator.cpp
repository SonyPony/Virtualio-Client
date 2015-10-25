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
    for(const QString key: object.keys())
        expectedKeys.removeAll(key);

    if(expectedKeys.length()) {
        QString errorMsg = QString("Expected %1 keys").arg(expectedKeys.join(", "));
        Q_EMIT error(errorMsg);
        return errorMsg;
    }

    return QStringLiteral("");
}

QString SettingsValidator::checkValues(QList<QPair<QString, QJsonValue::Type> > pairs, QJsonObject object)
{
    for(const QPair<QString, QJsonValue::Type> value: pairs) {
        if(object[value.first].type() != value.second) {
            const QString errorMsg = QString("At key %1 expected value type %2 intead of %3")
                    .arg(value.first)
                    .arg(this->type(value.second))
                    .arg(this->type(object[value.first].type()));
            Q_EMIT error(errorMsg);
            return errorMsg;
        }
    }

    return QStringLiteral("");
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

QString SettingsValidator::checkRootObject(QJsonObject object)
{
    QStringList expectedKeys = { "name", "tagStyle", "tagOptions", "moduleSettings" };
    return checkKeys(expectedKeys, object);
}

QString SettingsValidator::checkTagStyle(QJsonObject object)
{
    QStringList expectedKeys = { "primaryColor", "secondaryColor" };
    QString error = checkKeys(expectedKeys, object["tagStyle"].toObject());

    if(!error.isEmpty())
        return error;

    QList<QPair<QString, QJsonValue::Type> > expectedValueTypes = {
        qMakePair(QStringLiteral("primaryColor"), QJsonValue::String),
        qMakePair(QStringLiteral("secondaryColor"), QJsonValue::String)
    };

    return checkValues(expectedValueTypes, object["tagStyle"].toObject());
}

QString SettingsValidator::checkTagOptions(QJsonObject object)
{

}

QString SettingsValidator::checkModuleSettings(QJsonObject object)
{

}

