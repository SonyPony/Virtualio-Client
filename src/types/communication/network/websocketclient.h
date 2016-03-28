#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QQuickItem>
#include <QtWebSockets/QtWebSockets>

class WebsocketClient : public QQuickItem
{
        Q_OBJECT
        Q_ENUMS(Statuses)
        Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
        Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

    private:
        int m_status;
        QUrl m_url;
        QWebSocket m_socket;

    public:
        explicit WebsocketClient(QQuickItem *parent = 0);

        enum Statuses {Open, Closed};

        Q_INVOKABLE void sendTextMessage(QString message);
        Q_INVOKABLE void reconnect();
        int status() const;
        QUrl url() const;

    public slots:
        void close();
        void setUrl(QUrl url);
        void setStatus(int status);

    private slots:
        void resendMessageSignal(QString message);
        void onConnected();
        void onDisconnected();

    signals:
        void textMessageReceived(QString message);
        void statusChanged(int status);
        void urlChanged(QUrl url);
};

#endif // WEBSOCKETCLIENT_H
