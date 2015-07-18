#include "graphaxis.h"
#include "core/interval.h"
#include <QPainter>
#include <QVector>

GraphAxis::GraphAxis(): AbstractGraphAxis()
{
    m_lineWidth = 1;
    m_font = "Arial";
    m_fontSize = 10;
}

void GraphAxis::paintHorizontalAxis(QPainter *painter)
{
    int offset = 10;
    int count = calculateValuesCount(m_verticalRatio, m_valuesCount);

    //setting painter for drawing text
    painter->setFont(font);
    painter->setPen(QPen(m_textColor));
}

void GraphAxis::paintVerticalAxis(QPainter *painter)
{
    //it is for font metrics
    QString intervalMin = QString::number(m_values->min(), 'f', 1);
    QString intervalMax = QString::number(m_values->max(), 'f', 1);
    QFont font(m_font, m_fontSize);
    QFontMetrics fm(font);
    QVector<QLineF> axisLines;
    QSize content;
    int offset = 10;
    int count = calculateValuesCount(m_verticalRatio, m_valuesCount);
    double piece = (height() - lineWidth()) / (count - 1);
    int textWidth = (intervalMin.length() > intervalMax.length())
                    ?fm.width(intervalMin)
                    :fm.width(intervalMax);
    content.setWidth(width() - textWidth);

    //setting painter for drawing text
    painter->setFont(font);
    painter->setPen(QPen(m_textColor));

    //first calculating vertical axis
    for(int i = 0; i < count; i++) {
        int y = piece * i ;//+ m_lineWidth / 2;// + m_verticalRatio - 1;
        QLineF line(width() - content.width() + offset, y, width(), y);
        axisLines.append(line);
        if(i != 0 && i < count - 1)
        painter->drawText(QPoint(0, y + m_fontSize / 2), m_labels[count - i - 1]);
    }

    //set color for drawing lines
    painter->setPen(QPen(m_color,
                         m_lineWidth));
    painter->drawLines(axisLines);
}

void GraphAxis::paint(QPainter *painter)
{
    if(m_enabledDirections & GraphAxis::Vertical)
        paintVerticalAxis(painter);
    else if(m_enabledDirections & GraphAxis::Horizontal)
        paintHorizontalAxis(painter);
}

QString GraphAxis::font() const
{
    return m_font;
}

QColor GraphAxis::textColor() const
{
    return m_textColor;
}

QColor GraphAxis::color() const
{
    return m_color;
}

int GraphAxis::lineWidth() const
{
    return m_lineWidth;
}

int GraphAxis::fontSize() const
{
    return m_fontSize;
}

void GraphAxis::setFont(QString font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void GraphAxis::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void GraphAxis::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    emit colorChanged(color);
}

void GraphAxis::setLineWidth(int lineWidth)
{
    if (m_lineWidth == lineWidth)
        return;

    m_lineWidth = lineWidth;
    emit lineWidthChanged(lineWidth);
}

void GraphAxis::setFontSize(int fontSize)
{
    if (m_fontSize == fontSize)
        return;

    m_fontSize = fontSize;
    emit fontSizeChanged(fontSize);
}
