#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>
#include "serialcommunication.h"

class MessageManager : public QObject
{
        Q_OBJECT
        Q_PROPERTY(SerialCommunication* serial READ serial WRITE setSerial NOTIFY serialChanged)

    protected:
        SerialCommunication* m_serial;

    public:
        MessageManager(QObject *parent = 0);

        SerialCommunication* serial() const;

    protected Q_SLOTS:
        void connectSerial();
        void handleMessage(QString msg);

    public Q_SLOTS:
        void requestVerification();

        void setSerial(SerialCommunication* serial);

    Q_SIGNALS:
        void verified();
        void serialChanged(SerialCommunication* serial);
};

#endif // MESSAGEMANAGER_H
