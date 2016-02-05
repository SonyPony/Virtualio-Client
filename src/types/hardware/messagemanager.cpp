#include "messagemanager.h"

MessageManager::MessageManager(QObject *parent) : QObject(parent)
{
    m_serial = NULL;

    connect(this, &MessageManager::serialChanged, this, &MessageManager::connectSerial);
}

SerialCommunication *MessageManager::serial() const
{
    return m_serial;
}

void MessageManager::connectSerial()
{
    connect(m_serial, &SerialCommunication::message, this, &MessageManager::handleMessage);
}

void MessageManager::handleMessage(QString msg)
{
    if(msg == "VIOVerification1811")
        qDebug() << msg;
}

void MessageManager::requestVerification()
{
    //m_serial->send
}

void MessageManager::setSerial(SerialCommunication *serial)
{
    if (m_serial == serial)
        return;

    m_serial = serial;
    emit serialChanged(serial);
}

