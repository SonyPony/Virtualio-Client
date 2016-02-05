#ifndef STEPPROGRESS_H
#define STEPPROGRESS_H

#include <QQuickItem>
#include "abstracttabselection.h"
#include <QPainter>

class StepProgress : public AbstractTabSelection
{
        Q_OBJECT
        Q_PROPERTY(int stepsCount READ stepsCount WRITE setStepsCount NOTIFY stepsCountChanged)
        Q_PROPERTY(int currentStep READ currentStep WRITE setCurrentStep NOTIFY currentStepChanged)
        Q_PROPERTY(QColor secondColor READ secondColor WRITE setSecondColor NOTIFY secondColorChanged)

    private:
        QColor m_secondColor;
        int m_currentStep;
        int m_stepsCount;

    public:
        StepProgress(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QColor secondColor() const;
        int currentStep() const;
        int stepsCount() const;

    public Q_SLOTS:
        void setSecondColor(QColor secondColor);
        void setCurrentStep(int currentStep);
        void setStepsCount(int stepsCount);

    Q_SIGNALS:
        void secondColorChanged(QColor secondColor);
        void currentStepChanged(int currentStep);
        void stepsCountChanged(int stepsCount);
};

#endif // STEPPROGRESS_H
