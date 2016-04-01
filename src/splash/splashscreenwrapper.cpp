#include "splashscreenwrapper.h"

SplashScreenWrapper::SplashScreenWrapper(QWidget *parent) : QQuickWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen | Qt::WindowStaysOnTopHint);
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);

    connect(m_timer, &QTimer::timeout, this, &SplashScreenWrapper::timeout);
    connect(this, &SplashScreenWrapper::timeout, this, &SplashScreenWrapper::close);
}

void SplashScreenWrapper::setTimeout(int timeout)
{
    m_timer->setInterval(timeout);
}

void SplashScreenWrapper::start()
{
    m_timer->start();
}

