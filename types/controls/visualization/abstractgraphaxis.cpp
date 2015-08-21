#include "abstractgraphaxis.h"

int AbstractGraphAxis::calculateValuesCount(double ratio, double valuesCount)
{
    return valuesCount * ratio - (ratio - 1);
}

AbstractGraphAxis::AbstractGraphAxis()
{
    m_values = new Interval();
    connect(this, SIGNAL(verticalRatioChanged(double)), this, SLOT(resizeAxis(double)));
    connect(this, SIGNAL(horizontalRatioChanged(double)), this, SLOT(resizeAxis(double)));
    connect(this, SIGNAL(valuesCountChanged(int)), this, SLOT(update()));
    connect(this, SIGNAL(valuesChanged(Interval*)), this, SLOT(update()));
    connect(this, SIGNAL(valuesChanged(Interval*)), this, SLOT(resizeAxis()));
    connect(this, SIGNAL(valuesCountChanged(int)), this, SLOT(resizeAxis()));
}

AbstractGraphAxis::~AbstractGraphAxis()
{
    m_values = NULL;
    m_ratio = NULL;
}

Interval *AbstractGraphAxis::values() const
{
    return m_values;
}

int AbstractGraphAxis::valuesCount() const
{
    return m_valuesCount;
}

double AbstractGraphAxis::ratio() const
{
    return *m_ratio;
}

void AbstractGraphAxis::setVerticalRatio(double verticalRatio)
{
    if (m_verticalRatio == verticalRatio || ~m_enabledDirections & ResizeAbleItem::Vertical)
        return;

    double ratio = (double)(calculateValuesCount(verticalRatio, m_valuesCount) - 1) / (double)(calculateValuesCount(m_verticalRatio, m_valuesCount) - 1);
    setHeight(height() * ratio);

    m_verticalRatio = verticalRatio;
    emit verticalRatioChanged(verticalRatio);
}

void AbstractGraphAxis::resizeAxis(double ratio)
{
    m_labels = QStringList();
    int count = calculateValuesCount(ratio, m_valuesCount);
    double piece = m_values->length() / (count - 1);

    for(int i = 0; i < count; i++)
        m_labels.append(QString::number(m_values->min() + i * piece, 'f', 1));
}

void AbstractGraphAxis::resizeAxis()
{
    m_labels = QStringList();
    int count = calculateValuesCount(*m_ratio, m_valuesCount);
    double piece = m_values->length() / (count - 1);

    for(int i = 0; i < count; i++)
        m_labels.append(QString::number(m_values->min() + i * piece, 'f', 1));
}

void AbstractGraphAxis::setValues(Interval *values)
{
    if (m_values == values)
        return;

    m_values = values;
    emit valuesChanged(values);
}

void AbstractGraphAxis::setValuesCount(int valuesCount)
{
    if (m_valuesCount == valuesCount)
        return;

    m_valuesCount = valuesCount;
    emit valuesCountChanged(valuesCount);
}

void AbstractGraphAxis::setRatio(double ratio)
{
    if (*m_ratio == ratio)
        return;

    if(m_enabledDirections & AbstractGraphAxis::Vertical)
        setVerticalRatio(ratio);
    else if(m_enabledDirections & AbstractGraphAxis::Horizontal)
        setHorizontalRatio(ratio);
    emit ratioChanged(ratio);
}

