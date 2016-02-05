#include "stepprogress.h"

StepProgress::StepProgress(QQuickItem *parent): AbstractTabSelection(parent)
{
    connect(this, &StepProgress::currentStepChanged, this, &QQuickItem::update);
}

void StepProgress::paint(QPainter *painter)
{
    const double width = this->width();
    const double height = this->height();
    const QSizeF dotSize(height, height);
    const double step = (width - dotSize.width()) /( m_stepsCount - 1);

    QColor dotColor;
    QPointF dotPosCenter(0, height / 2.);

    painter->setRenderHint(QPainter::Antialiasing);

    for(int i = 0; i < m_stepsCount; i++) {
        dotPosCenter.setX(i * step + dotSize.width() / 2.);

        if(i == m_currentStep)
            dotColor = m_color;
        else
            dotColor = m_secondColor;

        painter->setPen(dotColor);
        painter->setBrush(dotColor);
        painter->drawEllipse(dotPosCenter, dotSize.width() / 2., dotSize.height() / 2.);
    }
}

QColor StepProgress::secondColor() const
{
    return m_secondColor;
}

int StepProgress::currentStep() const
{
    return m_currentStep;
}

int StepProgress::stepsCount() const
{
    return m_stepsCount;
}

void StepProgress::setSecondColor(QColor secondColor)
{
    if (m_secondColor == secondColor)
        return;

    m_secondColor = secondColor;
    emit secondColorChanged(secondColor);
}

void StepProgress::setCurrentStep(int currentStep)
{
    if (m_currentStep == currentStep)
        return;

    m_currentStep = currentStep;
    emit currentStepChanged(currentStep);
}

void StepProgress::setStepsCount(int stepsCount)
{
    if (m_stepsCount == stepsCount)
        return;

    m_stepsCount = stepsCount;
    emit stepsCountChanged(stepsCount);
}

