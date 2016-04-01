#ifndef SPLASHSCREENWRAPPER_H
#define SPLASHSCREENWRAPPER_H

#include <QWidget>
#include <QQuickWidget>
#include <QTimer>

class SplashScreenWrapper : public QQuickWidget
{
        Q_OBJECT
    private:
        QTimer* m_timer;

    public:
        SplashScreenWrapper(QWidget *parent = 0);

        void setTimeout(int timeout);

    public Q_SLOTS:
        void start();

    Q_SIGNALS:
        void timeout();
};

#endif // SPLASHSCREENWRAPPER_H
