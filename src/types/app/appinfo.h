#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>

class AppStates: public QObject {
        Q_OBJECT
        Q_ENUMS(Modes)
        Q_ENUMS(ConnectionStates)

    public:
        enum Modes {
            Stopped,
            Running
        };

        enum ConnectionStates {
            Disconnected,
            Connected
        };
};

class AppInfo : public QObject
{
        Q_OBJECT
        Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)
        Q_PROPERTY(int connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)

    private:
        int m_mode;
        int m_connectionState;

    public:
        AppInfo(QObject *parent = 0);

        int mode() const;
        int connectionState() const;

    public Q_SLOTS:
        void setMode(int mode);
        void setConnectionState(int connectionState);

    Q_SIGNALS:
        void modeChanged(int mode);
        void connectionStateChanged(int connectionState);
};

#endif // APPINFO_H
