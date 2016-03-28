#include "messagemanager.h"
#include <QJsonValue>
#include <QMetaEnum>
#include <QJsonDocument>

MessageManager::MessageManager(QObject *parent) : QObject(parent)
{

}

QString MessageManager::verificationRequestMsg()
{
    QJsonObject message;
    message.insert("type", QJsonValue("verification"));
    message.insert("code", QJsonValue("VIOVerification1811"));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::initPinMsg(int pin, MessageManager::PinType pinType)
{
    static const int enumIndex = this->metaObject()->indexOfEnumerator("PinType");
    static const QMetaEnum pinsTypeEnum = this->staticMetaObject.enumerator(enumIndex);

    return this->initPinMsg(pin, pinsTypeEnum.valueToKey(pinType));
}

QString MessageManager::initPinMsg(int pin, QString pinType)
{
    QJsonObject message;
    message.insert("type", QJsonValue("init_pin"));
    message.insert("pin", QJsonValue(pin));

    message.insert("pinType", QJsonValue(pinType));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::setPinMsg(int pin, QString pinType, QVariant value)
{
    QJsonObject message;
    message.insert("type", QJsonValue("set_pin"));
    message.insert("pin", QJsonValue(pin));

    message.insert("pinType", QJsonValue(pinType));
    message.insert("value", QJsonValue::fromVariant(value));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::codeMsg(QString scriptCode)
{
    QJsonObject message;
    message.insert("type", QJsonValue("script_code"));
    message.insert("code", QJsonValue(scriptCode));

    return QString(QJsonDocument(message).toJson());
}

void MessageManager::handleMessage(QJsonObject msg)
{
    const QString msgType = msg["type"].toString();

    if(msgType == QStringLiteral("verification")) {
        if(msg["code"].toString() == QStringLiteral("VIOVerification1811"))
            Q_EMIT this->verified();
    }

    else if(msgType == QStringLiteral("read_digital_pin")) {
        Q_EMIT this->readDigitalPin(msg["pin"].toInt(), msg["state"].toInt());
    }
}

