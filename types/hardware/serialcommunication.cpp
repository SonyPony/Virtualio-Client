#include "serialcommunication.h"

SerialCommunication::SerialCommunication()
{
    m_messageBuffer = "";
    m_connected = false;
    QObject::connect(this, SIGNAL(found()), this, SLOT(setPort()));
}

SerialCommunication::~SerialCommunication() {}

QString SerialCommunication::portIdentifier() const
{
    return m_portIdentifier;
}

QString SerialCommunication::portName() const
{
    return m_portName;
}

bool SerialCommunication::connected() const
{
    return m_connected;
}

void SerialCommunication::setPort()
{
    m_serial = new QSerialPort(m_serialInfo);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!m_serial->open(QIODevice::ReadWrite))
        emit error("Unable to connect.");

    QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void SerialCommunication::handleReadyRead()
{
    m_messageBuffer += QString(m_serial->readAll());
    QStringList separatedData;
    if(m_messageBuffer.contains(QString(";"), Qt::CaseInsensitive)) {
        separatedData = m_messageBuffer.split(";", QString::KeepEmptyParts, Qt::CaseInsensitive);

        emit message(separatedData.at(0));

        if(separatedData.length() > 1)
            m_messageBuffer = separatedData.at(1);
    }
}

void SerialCommunication::setPortIdentifier(QString arg)
{
    if (m_portIdentifier == arg)
        return;

    m_portIdentifier = arg;
    emit portIdentifierChanged(arg);
}

void SerialCommunication::setPortName(QString arg)
{
    if (m_portName == arg)
        return;

    m_portName = arg;
    emit portNameChanged(arg);
}


void SerialCommunication::tryConnect()
{
    foreach (const QSerialPortInfo singlePort, QSerialPortInfo::availablePorts()) {
        if(singlePort.description().contains(m_portIdentifier, Qt::CaseInsensitive)) {
            m_serialInfo = singlePort;
            qDebug() << m_serialInfo.portName();
            setConnected(true);
            emit found();
            return;
        }
    }

    emit error("Unable to connect.");
}

void SerialCommunication::setConnected(bool arg)
{
    if (m_connected == arg)
        return;

    m_connected = arg;
    emit connectedChanged(arg);
}
