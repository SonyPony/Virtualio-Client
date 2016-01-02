#include "graphaxis.h"
#include "interval.h"
#include <QPainter>
#include <QVector>
#include <stdexcept>

GraphAxis::GraphAxis(): AbstractGraphAxis()//, m_ratio(3)
{
    m_lineWidth = 1;
    m_font = "Arial";
    m_fontSize = 10;
    m_textMode = ExcludeNone;
    m_gridMode = ExcludeNone;
    m_ratio = NULL;
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, SIGNAL(textModeChanged(int)), this, SLOT(update()));
    connect(this, SIGNAL(enabledDirectionsChanged(int)), this, SLOT(setRatioBinding(int)));
    connect(this, SIGNAL(fontSizeChanged(int)), this, SLOT(calculateOffset()));
    connect(this, SIGNAL(valuesChanged(Interval*)), this, SLOT(calculateOffset()));
    connect(this, SIGNAL(enabledDirectionsChanged(int)), this, SLOT(calculateOffset()));
}

GraphAxis::GraphAxis(GraphAxis *other)
{
    m_font = other->font();
    m_textColor = other->textColor();
    m_color = other->color();
    m_lineWidth = other->lineWidth();
    m_fontSize = other->fontSize();
    m_offset = other->offset();
    m_graphPaintProperties = other->graphPaintProperties();
    m_textMode = other->textMode();
    m_gridMode = other->gridMode();
    m_values = other->values();
    m_valuesCount = other->valuesCount();
    m_enabledDirections = other->enabledDirections();
}

GraphAxis::~GraphAxis()
{
    m_ratio = NULL;
}

void GraphAxis::paint(QPainter *painter)
{
    QFont font(m_font, m_fontSize);
    m_graphPaintProperties.count = calculateValuesCount(*m_ratio, m_valuesCount);

    if(m_enabledDirections & GraphAxis::Vertical) {
        m_graphPaintProperties.piece = (height() - m_lineWidth) / (m_graphPaintProperties.count - 1);
        m_graphPaintProperties.calculateLinePos = [&](int i) -> QLineF {
            return QLineF(m_offset, m_graphPaintProperties.piece * i, width(), m_graphPaintProperties.piece * i);
        };
        m_graphPaintProperties.calculateTextPos = [&](int i) -> QPointF {
            return QPointF(0, m_graphPaintProperties.piece * i + m_fontSize / 2);
        };
        m_graphPaintProperties.getText = [&](int i) -> QString {
            return m_labels[m_graphPaintProperties.count - i - 1];
        };
    }
    else if(m_enabledDirections & GraphAxis::Horizontal) {
        m_graphPaintProperties.piece = (width() - m_lineWidth) / (m_graphPaintProperties.count - 1);
        m_graphPaintProperties.calculateLinePos = [&](int i) -> QLineF {
            return QLineF(m_graphPaintProperties.piece * i, 0, m_graphPaintProperties.piece * i, height() - m_offset - 1);
        };
        m_graphPaintProperties.calculateTextPos = [&](int i) -> QPointF {
            QFontMetrics fm(font);
            return QPointF(m_graphPaintProperties.piece * i - fm.width(m_labels[m_graphPaintProperties.count - i - 1]) / 2, height());
        };
        m_graphPaintProperties.getText = [&](int i) -> QString {
            return m_labels[i];
        };
    }

    QVector<QLineF> axisLines;

    //setting painter for drawing text
    painter->setFont(font);
    painter->setPen(QPen(m_textColor));

    for(int i = 0; i < m_graphPaintProperties.count; i++) {
        switch (m_gridMode) {       //selecting grid mode
            case ExcludeOdd:
                if(i % 2 && m_gridMode == ExcludeOdd)
                    break;
            case ExcludeEven:
                if(i % 2 == 0 && m_gridMode == ExcludeEven)
                    break;

            case ExcludeFirstAndLast:
            case ExcludeFirst:
                if(!i && (m_gridMode == ExcludeFirst || m_gridMode == ExcludeFirstAndLast))
                    break;
            case ExcludeLast:
                if(i == m_graphPaintProperties.count - 1  && (m_gridMode == ExcludeLast || m_gridMode == ExcludeFirstAndLast))
                    break;
            default:
                axisLines.append(m_graphPaintProperties.calculateLinePos(i));
                break;
        }

        switch (m_textMode) {       //selecting text mode
            case ExcludeOdd:
                if(i % 2 && m_textMode == ExcludeOdd)
                    break;
            case ExcludeEven:
                if(i % 2 == 0 && m_textMode == ExcludeEven)
                    break;

            case ExcludeFirstAndLast:
            case ExcludeLast:
                if(!i && (m_textMode == ExcludeLast || m_textMode == ExcludeFirstAndLast))
                    break;
            case ExcludeFirst:
                if(i == m_graphPaintProperties.count - 1  && (m_textMode == ExcludeFirst || m_textMode == ExcludeFirstAndLast))
                    break;
            default:
                painter->drawText(m_graphPaintProperties.calculateTextPos(i), m_graphPaintProperties.getText(i));
                break;
        }
    }

    painter->setPen(QPen(m_color, m_lineWidth));
    painter->drawLines(axisLines);

    emit propertiesReady();
}

void GraphAxis::wheelEvent(QWheelEvent *e)
{
    if(e->angleDelta().y() > 0)
        setRatio(*m_ratio + 1);
    else {
        if(*m_ratio - 1)        //minimal ratio is 1
            setRatio(*m_ratio - 1);
    }
}

QPoint GraphAxis::calculatePointPos(double value)
{
    Q_ASSERT_X(m_values->isIn(value), "GraphAxis", "Value out of range");

    double valueRelativePos = m_values->valuePos(value);

    if(m_enabledDirections & GraphAxis::Vertical)
        return QPoint(m_offset, height() - valueRelativePos * height());
    else
        return QPoint(valueRelativePos * width(), m_offset);

}

void GraphAxis::calculateOffset()
{
    const int offset = 10;

    if(m_enabledDirections & GraphAxis::Vertical) {
        QString intervalMin = QString::number(m_values->min(), 'f', 1);
        QString intervalMax = QString::number(m_values->max(), 'f', 1);
        QFont font(m_font, m_fontSize);
        QFontMetrics fm(font);

        const int textWidth = (intervalMin.length() > intervalMax.length())
                        ?fm.width(intervalMin)
                        :fm.width(intervalMax);
        m_offset = offset + textWidth;
    }

    else if(m_enabledDirections & GraphAxis::Horizontal)
        m_offset = offset + m_fontSize;
    emit offsetChanged(m_offset);
}

void GraphAxis::setRatioBinding(int direction)
{
    if(direction & GraphAxis::Vertical)
        m_ratio = &m_verticalRatio;
    else if(direction & GraphAxis::Horizontal)
        m_ratio = &m_horizontalRatio;
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

int GraphAxis::offset() const
{
    return m_offset;
}

GraphPaintProperties GraphAxis::graphPaintProperties() const
{
    return m_graphPaintProperties;
}

int GraphAxis::textMode() const
{
    return m_textMode;
}

int GraphAxis::gridMode() const
{
    return m_gridMode;
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

void GraphAxis::setTextMode(int textMode)
{
    if (m_textMode == textMode)
        return;

    m_textMode = textMode;
    emit textModeChanged(textMode);
}

void GraphAxis::setGridMode(int gridMode)
{
    if (m_gridMode == gridMode)
        return;

    m_gridMode = gridMode;
    emit gridModeChanged(gridMode);
}


