#include "messagemanager.h"
#include <QJsonValue>
#include <QMetaEnum>
#include <QJsonDocument>
#include <QDebug>
#include <QRegularExpression>

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

QString MessageManager::initPinMsg(int pin, QString pinType, int baud, QString parity, QString stopBits)
{
    QJsonObject message;
    message.insert("type", QJsonValue("init_pin"));
    message.insert("pin", QJsonValue(pin));
    message.insert("baud", QJsonValue(baud));
    message.insert("parity", QJsonValue(parity));
    message.insert("stopBits", QJsonValue(stopBits));

    message.insert("pinType", QJsonValue(pinType));
    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::setPinMsg(int pin, QVariant value)
{
    QJsonObject message;
    message.insert("type", QJsonValue("set_pin"));
    message.insert("pin", QJsonValue(pin));

    message.insert("value", QJsonValue::fromVariant(value));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::sendCharMsg(int pin, QVariant value)
{
    QJsonObject message;
    message.insert("type", QJsonValue("send_char"));
    message.insert("pin", QJsonValue(pin));

    // converting value
    int convertedValue;
    bool ok = true;
    QString sValue = value.toString();

    if(sValue.contains(QRegularExpression("^\'.\'$"))) {
        if(sValue[1].unicode() > 255) {
            Q_EMIT this->error(tr("Trying to sned unsupported character."));
            return QString();
        }

        else
            convertedValue = sValue[1].cell();
    }

    else if(sValue.contains(QRegularExpression("^0b[1|0]{8}$"))) {
        sValue.remove("0b");
        convertedValue = sValue.toInt(&ok, 2);
    }
    else if(sValue.contains(QRegularExpression("^0x[a-fA-F0-9]{2}$"))) {
        sValue.remove("0x");
        convertedValue = sValue.toInt(&ok, 16);
    }

    else if(sValue.contains(QRegularExpression("^\\d\\d?\\d?$"))) {
        convertedValue = sValue.toInt(&ok, 10);

        if(convertedValue > 255) {
            Q_EMIT this->error(tr("Entered number is to big."));
            return QString();
        }
    }

    else{
        Q_EMIT this->error(tr("Entered datas are not valid."));
        return QString();
    }

    message.insert("value", QJsonValue(convertedValue));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::codeMsg(QString scriptCode)
{
    QJsonObject message;
    message.insert("type", QJsonValue("script_code"));
    message.insert("code", QJsonValue(scriptCode));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::initDoneMsg()
{
    QJsonObject message;
    message.insert("type", QJsonValue("init_done"));

    return QString(QJsonDocument(message).toJson());
}

QString MessageManager::stopMsg()
{
    QJsonObject message;
    message.insert("type", QJsonValue("stop"));

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

