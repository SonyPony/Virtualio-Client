#include "appinfo.h"

AppInfo::AppInfo(QObject *parent) : QObject(parent)
{
    m_mode = (int)AppStates::Stopped;
    m_connectionState = (int)AppStates::Disconnected;
}

int AppInfo::mode() const
{
    return m_mode;
}

int AppInfo::connectionState() const
{
    return m_connectionState;
}

void AppInfo::setMode(int mode)
{
    if (m_mode == mode)
        return;

    m_mode = mode;
    emit modeChanged(mode);
}

void AppInfo::setConnectionState(int connectionState)
{
    if (m_connectionState == connectionState)
        return;

    m_connectionState = connectionState;
    emit connectionStateChanged(connectionState);
}

