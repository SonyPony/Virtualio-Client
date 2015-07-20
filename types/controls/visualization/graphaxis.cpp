#include "graphaxis.h"
#include "core/interval.h"
#include <QPainter>
#include <QVector>


GraphAxis::GraphAxis(): AbstractGraphAxis()
{
    m_lineWidth = 1;
    m_font = "Arial";
    m_fontSize = 10;
    m_ratio = NULL;
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, SIGNAL(enabledDirectionsChanged(int)), this, SLOT(setRatioBinding(int)));
    connect(this, SIGNAL(fontSizeChanged(int)), this, SLOT(calculateOffset()));
    connect(this, SIGNAL(valuesChanged(Interval*)), this, SLOT(calculateOffset()));
    connect(this, SIGNAL(enabledDirectionsChanged(int)), this, SLOT(calculateOffset()));
}

GraphAxis::~GraphAxis()
{
    m_ratio = NULL;
}

void GraphAxis::paint(QPainter *painter)
{
    GraphPaintProperties p;
    QFont font(m_font, m_fontSize);
    p.count = calculateValuesCount(*m_ratio, m_valuesCount);

    if(m_enabledDirections & GraphAxis::Vertical) {
        p.piece = (height() - m_lineWidth) / (p.count - 1);
        p.calculateLinePos = [&](int i) -> QLineF {
            return QLineF(m_offset, p.piece * i, width(), p.piece * i);
        };
        p.calculateTextPos = [&](int i) -> QPointF {
            return QPointF(0, p.piece * i + m_fontSize / 2);
        };
        p.getText = [&](int i) -> QString {
            return m_labels[p.count - i - 1];
        };

    }
    else if(m_enabledDirections & GraphAxis::Horizontal) {
        p.piece = (width() - m_lineWidth) / (p.count - 1);
        p.calculateLinePos = [&](int i) -> QLineF {
            return QLineF(p.piece * i, 0, p.piece * i, height() - m_offset);
        };
        p.calculateTextPos = [&](int i) -> QPointF {
            QFontMetrics fm(font);
            return QPointF(p.piece * i - fm.width(m_labels[p.count - i - 1]) / 2, height());
        };
        p.getText = [&](int i) -> QString {
            return m_labels[i];
        };
    }

    QVector<QLineF> axisLines;

    //setting painter for drawing text
    painter->setFont(font);
    painter->setPen(QPen(m_textColor));

    for(int i = 0; i < p.count; i++) {
        axisLines.append(p.calculateLinePos(i));
        if(i > 0 && i < p.count - 1)    //do not draw first and last
            painter->drawText(p.calculateTextPos(i), p.getText(i));
    }

    painter->setPen(QPen(m_color, m_lineWidth));
    painter->drawLines(axisLines);
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

double GraphAxis::ratio() const
{
    return *m_ratio;
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


void GraphAxis::setRatio(double ratio)
{
    if (*m_ratio == ratio)
        return;

    if(m_enabledDirections & GraphAxis::Vertical)
        setVerticalRatio(ratio);
    else if(m_enabledDirections & GraphAxis::Horizontal)
        setHorizontalRatio(ratio);
    emit ratioChanged(ratio);
}
