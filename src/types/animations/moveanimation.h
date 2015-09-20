#ifndef MOVEANIMATION_H
#define MOVEANIMATION_H

#include <QObject>
#include <QPointF>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class MoveAnimation : public QObject
{
        Q_OBJECT
        Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
        Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
        Q_PROPERTY(QEasingCurve easingCurve READ easingCurve WRITE setEasingCurve NOTIFY easingCurveChanged)
        Q_PROPERTY(QPointF startValue READ startValue WRITE setStartValue NOTIFY startValueChanged)
        Q_PROPERTY(QPointF endValue READ endValue WRITE setEndValue NOTIFY endValueChanged)

    private:
        QPropertyAnimation* m_xAnimation;
        QPropertyAnimation* m_yAnimation;
        QParallelAnimationGroup* m_moveAnimation;
        int m_duration;
        QObject* m_target;
        QEasingCurve m_easingCurve;
        QPointF m_startValue;
        QPointF m_endValue;

    public:
        MoveAnimation(QObject *parent = 0);
        MoveAnimation(QObject* target, int duration, QObject *parent = 0);

        int duration() const;
        QObject* target() const;
        QEasingCurve easingCurve() const;
        QPointF startValue() const;
        QPointF endValue() const;

    public slots:
        void start();
        void stop();
        void resume();
        void pause();

        void setDuration(int duration);
        void setTarget(QObject* target);
        void setEasingCurve(QEasingCurve easingCurve);
        void setStartValue(QPointF startValue);
        void setEndValue(QPointF endValue);

    signals:
        void durationChanged(int duration);
        void targetChanged(QObject* target);
        void easingCurveChanged(QEasingCurve easingCurve);
        void startValueChanged(QPointF startValue);
        void endValueChanged(QPointF endValue);
};

#endif // MOVEANIMATION_H
