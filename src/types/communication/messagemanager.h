#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QJsonObject>
#include <QObject>
#include <QVariant>

class MessageManager : public QObject
{
        Q_OBJECT
        Q_ENUMS(PinType)
    protected:

    public:
        MessageManager(QObject *parent = 0);

        enum PinType {
            DigitalIn,
            DigitalOut,
            UARTTX,
            UARTRX
        };

    public Q_SLOTS:
        QString verificationRequestMsg();
        QString initPinMsg(int pin, PinType pinType);
        QString initPinMsg(int pin, QString pinType);
        QString initPinMsg(int pin, QString pinType, int baud, QString parity, QString stopBits);
        QString setPinMsg(int pin, QVariant value);
        QString sendCharMsg(int pin, QVariant value);
        QString codeMsg(QString scriptCode);

        void handleMessage(QJsonObject msg);

    Q_SIGNALS:
        void readDigitalPin(int pin, int pinState);
        void verified();
        void error(QString msg);
};

#endif // MESSAGEMANAGER_H
