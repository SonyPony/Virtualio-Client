#include "AbstractGraphcontent.h"
#include <QPainter>

AbstractGraphContent::AbstractGraphContent(): ResizeAbleItem(), m_verticalAxis(NULL), m_horizontalAxis(NULL)
{
}

AbstractGraphContent::~AbstractGraphContent()
{
    m_verticalAxis = NULL;
    m_horizontalAxis = NULL;
}

QList<double> AbstractGraphContent::dataX() const
{
    return m_dataX;
}

QList<double> AbstractGraphContent::dataY() const
{
    return m_dataY;
}

GraphAxis *AbstractGraphContent::verticalAxis() const
{
    return m_verticalAxis;
}

GraphAxis *AbstractGraphContent::horizontalAxis() const
{
    return m_horizontalAxis;
}

void AbstractGraphContent::setHeightSameAsAxis()
{
    setHeight(m_verticalAxis->height());
}

void AbstractGraphContent::setWidthSameAsAxis()
{
    setWidth(m_horizontalAxis->width());
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

void AbstractGraphContent::setVerticalAxis(GraphAxis *verticalAxis)
{
    if (m_verticalAxis == verticalAxis)
        return;

    if(m_verticalAxis)
        disconnect(m_verticalAxis, SIGNAL(heightChanged()), this, SLOT(setHeightSameAsAxis()));

    m_verticalAxis = verticalAxis;

    setHeightSameAsAxis();
    connect(m_verticalAxis, SIGNAL(heightChanged()), this, SLOT(setHeightSameAsAxis()));
    emit verticalAxisChanged(verticalAxis);
}

void AbstractGraphContent::setHorizontalAxis(GraphAxis *horizontalAxis)
{
    if (m_horizontalAxis == horizontalAxis)
        return;

    if(m_horizontalAxis)
        disconnect(m_horizontalAxis, SIGNAL(widthChanged()), this, SLOT(setWidthSameAsAxis()));

    m_horizontalAxis = horizontalAxis;

    setWidthSameAsAxis();
    connect(m_horizontalAxis, SIGNAL(widthChanged()), this, SLOT(setWidthSameAsAxis()));
    emit horizontalAxisChanged(horizontalAxis);
}

