#include "serialcommunication.h"

SerialCommunication::SerialCommunication()
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    m_timer->setInterval(150);
    m_separator = QString(" ");

    m_portIdentifier = "";
    m_portName = "";
    m_messageBuffer = "";
    m_connectionState = SerialCommunication::Disconnected;
    m_connected = false;
    m_comPortsInfo = QStringList();

    connect(this, &SerialCommunication::found, this, &SerialCommunication::setPort);
    connect(m_timer, &QTimer::timeout, this, &SerialCommunication::updatePortsInfo);
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

int SerialCommunication::connectionState() const
{
    return m_connectionState;
}

QStringList SerialCommunication::comPortsInfo() const
{
    return m_comPortsInfo;
}

QString SerialCommunication::separator() const
{
    return m_separator;
}

void SerialCommunication::updatePortsInfo()
{
    QString comPortInfo;
    QStringList comPorts;

    for(const QSerialPortInfo singlePort: QSerialPortInfo::availablePorts()) {
        /*comPortInfo = QString("%1: Manufacturer: %2 Description: %3")
                .arg(singlePort.portName())
                .arg(singlePort.manufacturer())
                .arg(singlePort.description());*/
        comPortInfo = QString("%1")
                .arg(singlePort.portName());
        comPorts.append(comPortInfo);
    }

    if(m_comPortsInfo != comPorts) {
        m_comPortsInfo = comPorts;
        Q_EMIT this->comPortsInfoChanged(m_comPortsInfo);
    }
}

void SerialCommunication::setPort()
{
    m_serial = new QSerialPort(m_serialInfo);
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!m_serial->open(QIODevice::ReadWrite))
        emit error(tr("Unable to connect."));

    QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void SerialCommunication::handleReadyRead()
{
    m_messageBuffer += QString(m_serial->readAll());

    QStringList separatedData;
    if(m_messageBuffer.contains(m_separator, Qt::CaseSensitive)) {
        separatedData = m_messageBuffer.split(m_separator, QString::KeepEmptyParts, Qt::CaseSensitive);
        emit message(separatedData.at(0));

        if(separatedData.length() > 1)
            m_messageBuffer = separatedData.at(1);
    }
}

void SerialCommunication::setConnectionState(int arg)
{
    if(m_connectionState == arg)
        return;

    m_connectionState = arg;
    Q_EMIT this->connectionStateChanged(arg);
}

void SerialCommunication::startPeriodicUpdate()
{
    m_timer->start();
}

void SerialCommunication::stopPeriodicUpdate()
{
    m_timer->stop();
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
    this->updatePortsInfo();
    bool found = false;
    QSerialPortInfo portInfo;

    for(const QSerialPortInfo singlePort: QSerialPortInfo::availablePorts()) {
        if(!m_portIdentifier.isEmpty()) {
            if(singlePort.description().contains(m_portIdentifier, Qt::CaseSensitive)) {
                portInfo = singlePort;
                found = true;
                break;
            }
        }

        else if(!m_portName.isEmpty()) {
            if(singlePort.portName() == m_portName) {
                portInfo = singlePort;
                found = true;
                break;
            }
        }
    }

    if(found) {
        m_serialInfo = portInfo;
        qDebug() << "Found:" << m_serialInfo.portName();
        this->setConnected(true);
        Q_EMIT this->found();
        return;
    }


    Q_EMIT this->error("Unable to connect.");
}

void SerialCommunication::setConnected(bool arg)
{
    if (m_connected == arg)
        return;

    if(arg)
        this->setConnectionState(SerialCommunication::WaitingOnResponse);
    else
        this->setConnectionState(SerialCommunication::Disconnected);

    m_connected = arg;
    emit connectedChanged(arg);
}

void SerialCommunication::setSeparator(QString separator)
{
    if (m_separator == separator)
        return;

    m_separator = separator;
    emit separatorChanged(separator);
}
