#include "singleportdropdown.h"
#include <QPainter>

SinglePortDropDown::SinglePortDropDown(QQuickItem *parent): DropDown(parent)
{
    m_margin = 0;
    m_dataColors = QStringList();

    connect(this, &SinglePortDropDown::marginChanged, this, &QQuickItem::update);
    connect(this, &SinglePortDropDown::lineColorChanged, this, &QQuickItem::update);
}

void SinglePortDropDown::paint(QPainter *painter)
{
    DropDown::paint(painter);

    // draw title
    QRectF rect = this->boundingRect();
    rect.setHeight(m_titleFrameHeight);
    rect.setLeft(m_margin);

    painter->setFont(m_titleFont);
    painter->setPen(m_titleTextColor);
    painter->drawText(rect, m_title, QTextOption(Qt::AlignVCenter));

    // draw line
    // draw line
    painter->setPen(m_lineColor);
    painter->drawLine(0, m_titleFrameHeight - 1, this->width(), m_titleFrameHeight - 1);
}

QStringList SinglePortDropDown::dataColors() const
{
    return m_dataColors;
}

QColor SinglePortDropDown::lineColor() const
{
    return m_lineColor;
}

int SinglePortDropDown::margin() const
{
    return m_margin;
}

int SinglePortDropDown::dataPanelHeight() const
{
    return m_dataPanelHeight;
}

void SinglePortDropDown::addMessage(int data, int usTime)
{
    Q_ASSERT(data >= 0 && data <= 255);

    ByteDataPanel* dataPanel = new ByteDataPanel(this);
    dataPanel->setHeight(m_dataPanelHeight);
    dataPanel->setMargin(m_margin);
    dataPanel->setColor(m_contentColor);
    dataPanel->setData(data);
    dataPanel->setDataColors(m_dataColors);
    dataPanel->setTime(usTime);
    dataPanel->setDatasFont(m_contentFont);
    dataPanel->setLineColor(m_lineColor);

    connect(this, &SinglePortDropDown::marginChanged, dataPanel, &ByteDataPanel::setMargin);
    connect(this, &SinglePortDropDown::contentColorChanged, dataPanel, &ByteDataPanel::setColor);
    connect(this, &SinglePortDropDown::dataColorsChanged, dataPanel, &ByteDataPanel::setDataColors);
    connect(this, &SinglePortDropDown::contentFontChanged, dataPanel, &ByteDataPanel::setDatasFont);
    connect(this, &SinglePortDropDown::lineColorChanged, dataPanel, &ByteDataPanel::setLineColor);

    this->addItem(dataPanel);
    this->setContentFrameHeight(this->currentY());
}

void SinglePortDropDown::setDataColors(QStringList dataColors)
{
    if (m_dataColors == dataColors)
        return;

    m_dataColors = dataColors;
    emit dataColorsChanged(dataColors);
}

void SinglePortDropDown::setLineColor(QColor lineColor)
{
    if (m_lineColor == lineColor)
        return;

    m_lineColor = lineColor;
    emit lineColorChanged(lineColor);
}

void SinglePortDropDown::setMargin(int margin)
{
    if (m_margin == margin)
        return;

    m_margin = margin;
    emit marginChanged(margin);
}

void SinglePortDropDown::setDataPanelHeight(int dataPanelHeight)
{
    if (m_dataPanelHeight == dataPanelHeight)
        return;

    m_dataPanelHeight = dataPanelHeight;
    emit dataPanelHeightChanged(dataPanelHeight);
}

