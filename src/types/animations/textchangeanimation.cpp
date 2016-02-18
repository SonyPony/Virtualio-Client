#include "textchangeanimation.h"

TextChangeAnimation::TextChangeAnimation(QObject *parent): QPropertyAnimation(parent)
{
    m_currentText = "";
    m_startText = "";
    m_endText = "";
    m_textOpacity = 1;
    m_target = NULL;

    this->setTargetObject(this);
    this->setPropertyName("textOpacity");

    this->setKeyValueAt(0, 1);
    this->setKeyValueAt(0.5, 0);
    this->setKeyValueAt(1, 1);

    connect(this, &TextChangeAnimation::textOpacityChanged, this, &TextChangeAnimation::checkIfStepBeyondHalf);
    connect(this, &TextChangeAnimation::textOpacityChanged, [this]() {
        if(m_target != NULL)
            m_target->update();
    });
    connect(this, &TextChangeAnimation::startTextChanged, this, &TextChangeAnimation::setCurrentText);
    connect(this, &TextChangeAnimation::changeText, this, &TextChangeAnimation::setCurrentText);
}

QString TextChangeAnimation::endText() const
{
    return m_endText;
}

QString TextChangeAnimation::startText() const
{
    return m_startText;
}

double TextChangeAnimation::textOpacity() const
{
    return m_textOpacity;
}

QString TextChangeAnimation::currentText() const
{
    return m_currentText;
}

QQuickItem *TextChangeAnimation::target() const
{
    return m_target;
}

void TextChangeAnimation::setCurrentText(QString currentText)
{
    m_currentText = currentText;
}

void TextChangeAnimation::checkIfStepBeyondHalf()
{
    if(this->currentTime() >= this->duration() / 2.)
        Q_EMIT this->changeText(m_endText);
}

void TextChangeAnimation::setEndText(QString endText)
{
    if (m_endText == endText)
        return;

    m_endText = endText;
    emit endTextChanged(endText);
}

void TextChangeAnimation::setStartText(QString startText)
{
    if (m_startText == startText)
        return;

    m_startText = startText;
    emit startTextChanged(startText);
}

void TextChangeAnimation::setTextOpacity(double __textOpacity)
{
    if (m_textOpacity == __textOpacity)
        return;

    m_textOpacity = __textOpacity;
    emit textOpacityChanged(__textOpacity);
}

void TextChangeAnimation::setTarget(QQuickItem *targetObject)
{
    if (m_target == targetObject)
        return;

    m_target = targetObject;
    emit targetChanged(targetObject);
}

