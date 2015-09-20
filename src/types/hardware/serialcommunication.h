#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QQuickItem>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialCommunication : public QQuickItem
{
    Q_OBJECT
        Q_PROPERTY(QString portIdentifier READ portIdentifier WRITE setPortIdentifier NOTIFY portIdentifierChanged)
        Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
        Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

    private:
        QString m_portIdentifier;
        QString m_portName;
        QSerialPort *m_serial;
        QSerialPortInfo m_serialInfo;
        bool m_connected;
        QString m_messageBuffer;

    public:
        SerialCommunication();
        ~SerialCommunication();

        QString portIdentifier() const;
        QString portName() const;
        bool connected() const;

    private slots:
        void setPort();
        void handleReadyRead();

    public slots:
        void setPortIdentifier(QString arg);
        void setPortName(QString arg);
        void tryConnect();
        void setConnected(bool arg);

    signals:
        void message(QString arg);
        void found();
        void error(QString arg);

        void portIdentifierChanged(QString arg);
        void portNameChanged(QString arg);
        void connectedChanged(bool arg);
};

#endif // SERIALCOMMUNICATION_H
