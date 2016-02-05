#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QQuickItem>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

class SerialCommunication : public QQuickItem
{
        Q_OBJECT
        Q_ENUMS(ConnectionState)
        Q_PROPERTY(QString portIdentifier READ portIdentifier WRITE setPortIdentifier NOTIFY portIdentifierChanged)
        Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
        Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
        Q_PROPERTY(int connectionState READ connectionState NOTIFY connectionStateChanged)
        Q_PROPERTY(QStringList comPortsInfo READ comPortsInfo NOTIFY comPortsInfoChanged)
        Q_PROPERTY(QString separator READ separator WRITE setSeparator NOTIFY separatorChanged)

    private:
        QTimer* m_timer;
        QString m_portIdentifier;
        QString m_portName;
        QSerialPort *m_serial;
        QSerialPortInfo m_serialInfo;
        bool m_connected;
        QString m_messageBuffer;
        int m_connectionState;
        QStringList m_comPortsInfo;
        QString m_separator;

    public:
        enum ConnectionState {
            WaitingOnResponse,
            Connected,
            Disconnected
        };

        SerialCommunication();
        ~SerialCommunication();

        QString portIdentifier() const;
        QString portName() const;
        bool connected() const;
        int connectionState() const;
        QStringList comPortsInfo() const;
        QString separator() const;

    private Q_SLOTS:
        void setPort();
        void handleReadyRead();

    protected Q_SLOTS:
        void setConnectionState(int arg);

    public Q_SLOTS:
        void startPeriodicUpdate();
        void stopPeriodicUpdate();
        void updatePortsInfo();
        void setPortIdentifier(QString arg);
        void setPortName(QString arg);
        void tryConnect();
        void setConnected(bool arg);
        void setSeparator(QString separator);

    Q_SIGNALS:
        void message(QString arg);
        void found();
        void error(QString arg);

        void portIdentifierChanged(QString arg);
        void portNameChanged(QString arg);
        void connectedChanged(bool arg);
        void connectionStateChanged(int connectionState);
        void comPortsInfoChanged(QStringList comPortsInfo);
        void separatorChanged(QString separator);
};

#endif // SERIALCOMMUNICATION_H
