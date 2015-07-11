#include "AbstractGraphcontent.h"

AbstractGraphContent::AbstractGraphContent(): ResizeAbleItem()
{

}

QList<double> AbstractGraphContent::dataX() const
{
    return m_dataX;
}

QList<double> AbstractGraphContent::dataY() const
{
    return m_dataY;
}

void AbstractGraphContent::setDataX(QList<double> dataX)
{
    if (m_dataX == dataX)
        return;

    m_dataX = dataX;
    emit dataXChanged(dataX);
}

void AbstractGraphContent::setDataY(QList<double> dataY)
{
    if (m_dataY == dataY)
        return;

    m_dataY = dataY;
    emit dataYChanged(dataY);
}

