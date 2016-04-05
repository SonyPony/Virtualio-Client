#include "singleportdropdown.h"
#include <QPainter>

SinglePortDropDown::SinglePortDropDown(QQuickItem *parent): DropDown(parent)
{
    m_margin = 0;
    m_dataColors = QStringList();
    m_arrowRenderer = new QSvgRenderer(QStringLiteral(":/resources/images/arrowGray.svg"), this);
    m_blinkAnimation = new QPropertyAnimation(this, "titleColor", this);
    m_blinkAnimation->setLoopCount(-1);
    m_blinkAnimation->setDuration(2000);

    connect(this, &SinglePortDropDown::marginChanged, this, &QQuickItem::update);
    connect(this, &SinglePortDropDown::lineColorChanged, this, &QQuickItem::update);
    connect(this, &SinglePortDropDown::showed, this, &SinglePortDropDown::stopBlink);
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

    // draw arrow
    const double arrowSizeRatio = (m_titleFrameHeight * 0.2) / (double)m_arrowRenderer->defaultSize().height();
    const QSize arrowSize(
        m_arrowRenderer->defaultSize().width() * arrowSizeRatio,
        m_titleFrameHeight * 0.2
    );
    const QPointF arrowPos(
        this->width() - m_margin - arrowSize.width(),
        (m_titleFrameHeight - arrowSize.height()) / 2.
    );

    if(m_hidden) {
        painter->save();
        painter->translate(arrowPos.x() + arrowSize.width() / 2., m_titleFrameHeight / 2.);
        painter->rotate(-90);
        painter->translate(-(arrowPos.x() + arrowSize.width() / 2.), -m_titleFrameHeight / 2.);
    }
    m_arrowRenderer->render(painter, QRectF(arrowPos, arrowSize));
    if(m_hidden) {
        painter->restore();
    }

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

bool SinglePortDropDown::hidden() const
{
    return m_hidden;
}

void SinglePortDropDown::startBlink()
{
    m_originTitleColor = m_titleColor;
    m_blinkAnimation->setKeyValueAt(0, m_originTitleColor);
    m_blinkAnimation->setKeyValueAt(0.5, QColor("orange"));
    m_blinkAnimation->setKeyValueAt(1, m_originTitleColor);

    m_blinkAnimation->start();
}

void SinglePortDropDown::stopBlink()
{
    m_titleColor = m_originTitleColor;
    m_blinkAnimation->stop();
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

