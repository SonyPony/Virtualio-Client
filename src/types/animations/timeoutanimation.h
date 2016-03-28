#ifndef TIMEOUTANIMATION_H
#define TIMEOUTANIMATION_H

#include <QQuickItem>
#include <QPropertyAnimation>
#include <QPainter>
#include "painteditem.h"

class TimeoutAnimation : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)

    private:
        QPropertyAnimation *m_widthAnimation;
        int m_duration;

    public:
        TimeoutAnimation(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        int duration() const;

    public Q_SLOTS:
        void start();
        void stop();
        void resetAnimation();
        void setDuration(int duration);

    Q_SIGNALS:
        void timeout();
        void durationChanged(int duration);
};

#endif // TIMEOUTANIMATION_H
