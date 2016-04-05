#include "bytedatapanel.h"
#include <QPainter>

ByteDataPanel::ByteDataPanel(QQuickItem *parent): PaintedItem(parent)
{
    m_margin = 0;

    connect(this, &ByteDataPanel::dataChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::dataColorsChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::lineColorChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::timeChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::marginChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::datasFontChanged, &QQuickItem::update);
    connect(this, &ByteDataPanel::colorChanged, &QQuickItem::update);
}

void ByteDataPanel::paint(QPainter *painter)
{
    // has 4 data types + time
    if(m_dataColors.length() < 4 + 1)
        return;

    // draw background
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(this->boundingRect());

    // draw data
    QChar c(m_data);
    QChar resultChar;

    if(c.isLetterOrNumber())
        resultChar = c;
    else
        resultChar = '?';

    const QStringList maxDataLengthSamples = {
        "200",
        "0b11001100",
        "0xFF",
        "\'a\'"
    };
    const QStringList datas = {
        QString::number(m_data),                // dec
        "0b" + QString::number(m_data, 2),      // bin
        "0x" + QString::number(m_data, 16),     // hex
        QString("\'%1\'").arg( QChar(m_data))   // char
    };

    QRect rect = this->boundingRect().toRect();
    const QFontMetrics fm(m_datasFont);

    painter->setFont(m_datasFont);

    for(int i = 0; i < datas.length(); i++) {
        rect.setLeft(rect.x() + m_margin);
        painter->setPen(QColor(m_dataColors[i]));
        painter->drawText(rect, datas[i], QTextOption(Qt::AlignVCenter));

        rect.setLeft(rect.x() + fm.width(maxDataLengthSamples[i]));
    }

    rect.setRight(rect.x() + rect.width() - m_margin);
    painter->setPen(QColor(m_dataColors[4]));
    painter->drawText(
        rect,
        QString::number(m_time) + QStringLiteral("us"),
        QTextOption(Qt::AlignVCenter | Qt::AlignRight)
    );

    // draw line
    painter->setPen(m_lineColor);
    painter->drawLine(0, this->height() - 1, this->width(), this->height() - 1);
}

int ByteDataPanel::data() const
{
    return m_data;
}

QStringList ByteDataPanel::dataColors() const
{
    return m_dataColors;
}

QColor ByteDataPanel::lineColor() const
{
    return m_lineColor;
}

int ByteDataPanel::time() const
{
    return m_time;
}

int ByteDataPanel::margin() const
{
    return m_margin;
}

QFont ByteDataPanel::datasFont() const
{
    return m_datasFont;
}

void ByteDataPanel::setData(int data)
{
    if (m_data == data)
        return;

    Q_ASSERT(data >=0 && data <= 255);
    m_data = data;
    emit dataChanged(data);
}

void ByteDataPanel::setDataColors(QStringList dataColors)
{
    if (m_dataColors == dataColors)
        return;

    m_dataColors = dataColors;
    emit dataColorsChanged(dataColors);
}

void ByteDataPanel::setLineColor(QColor lineColor)
{
    if (m_lineColor == lineColor)
        return;

    m_lineColor = lineColor;
    emit lineColorChanged(lineColor);
}

void ByteDataPanel::setTime(int time)
{
    if (m_time == time)
        return;

    m_time = time;
    emit timeChanged(time);
}

void ByteDataPanel::setMargin(int margin)
{
    if (m_margin == margin)
        return;

    m_margin = margin;
    emit marginChanged(margin);
}

void ByteDataPanel::setDatasFont(QFont datasFont)
{
    if (m_datasFont == datasFont)
        return;

    m_datasFont = datasFont;
    emit datasFontChanged(datasFont);
}

