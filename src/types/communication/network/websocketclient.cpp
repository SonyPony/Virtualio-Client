#include "websocketclient.h"
#include <QtWebSockets/QtWebSockets>

WebsocketClient::WebsocketClient(QQuickItem *parent): QQuickItem(parent)
{
    m_status = -1;
    m_url = QUrl("");
    QObject::connect(&m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void WebsocketClient::sendTextMessage(QString message)
{
    m_socket.sendTextMessage(message);
}

void WebsocketClient::reconnect()
{
    m_socket.open(m_url);
}


void WebsocketClient::onConnected()
{
    setStatus(Open);
    QObject::connect(&m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(resendMessageSignal(QString)));
}

void WebsocketClient::onDisconnected()
{
    m_socket.close();
    QObject::disconnect(&m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(resendMessageSignal(QString)));
    setStatus(Closed);
}

int WebsocketClient::status() const
{
    return m_status;
}

QUrl WebsocketClient::url() const
{
    return m_url;
}

void WebsocketClient::setUrl(QUrl url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged(url);
}

void WebsocketClient::setStatus(int status)
{
    m_status = status;
    emit statusChanged(status);
}

void WebsocketClient::resendMessageSignal(QString message)
{
    emit textMessageReceived(message);
}

