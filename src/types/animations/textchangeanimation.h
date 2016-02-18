#ifndef TEXTCHANGEANIMATION_H
#define TEXTCHANGEANIMATION_H

#include <QObject>
#include <QQuickItem>
#include <QPropertyAnimation>

class TextChangeAnimation : public QPropertyAnimation
{
        Q_OBJECT
        Q_PROPERTY(QString startText READ startText WRITE setStartText NOTIFY startTextChanged)
        Q_PROPERTY(QString endText READ endText WRITE setEndText NOTIFY endTextChanged)
        Q_PROPERTY(double textOpacity READ textOpacity WRITE setTextOpacity NOTIFY textOpacityChanged)
        Q_PROPERTY(QQuickItem* target READ target WRITE setTarget NOTIFY targetChanged)

    private:
        QString m_currentText;
        QString m_endText;
        QString m_startText;
        double m_textOpacity;
        QQuickItem* m_target;

    public:
        TextChangeAnimation(QObject *parent = 0);

        QString endText() const;
        QString startText() const;
        double textOpacity() const;
        QString currentText() const;
        QQuickItem* target() const;

    private Q_SLOTS:
        void setCurrentText(QString currentText);
        void checkIfStepBeyondHalf();

    public Q_SLOTS:
        void setEndText(QString endText);
        void setStartText(QString startText);
        void setTextOpacity(double textOpacity);
        void setTarget(QQuickItem* target);

    Q_SIGNALS:
        void changeText(QString text);
        void endTextChanged(QString endText);
        void startTextChanged(QString startText);
        void textOpacityChanged(double textOpacity);
        void targetChanged(QQuickItem* target);
};

#endif // TEXTCHANGEANIMATION_H
