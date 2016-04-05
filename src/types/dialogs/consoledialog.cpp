#include "consoledialog.h"
#include <QPainter>

ConsoleDialog::ConsoleDialog(QQuickItem *parent): DropDown(parent)
{
    m_margin = 0;
    m_iconRenderer = new QSvgRenderer(QStringLiteral(":/resources/images/consoleIcon.svg"), this);

    this->unbindRepositioningContainer();

    connect(this, &ConsoleDialog::portsNamesChanged, this, &ConsoleDialog::generateDropDowns);
    connect(this, &ConsoleDialog::marginChanged, this, &QQuickItem::update);
}

void ConsoleDialog::paint(QPainter *painter)
{
    HideableWidget::paint(painter);

    // draw icon
    const double sizeRatio = (m_titleFrameHeight * 0.4) / (double)m_iconRenderer->defaultSize().height();
    const QSizeF iconSize(
        m_iconRenderer->defaultSize().width() * sizeRatio,
        (m_titleFrameHeight * 0.4)
    );
    const QPointF iconPos(
        m_margin,
        (m_titleFrameHeight - iconSize.height()) / 2.
    );

    m_iconRenderer->render(painter, QRectF(iconPos, iconSize));

    //draw title
    QRectF rect = this->boundingRect();
    rect.setLeft(iconPos.x() + iconSize.width() + m_margin);
    rect.setBottom(m_titleFrameHeight);
    painter->setPen(m_titleTextColor);
    painter->setFont(m_titleFont);
    painter->drawText(rect, m_title, QTextOption(Qt::AlignVCenter));
}

QStringList ConsoleDialog::portsNames() const
{
    return m_portsNames;
}

QQuickItem *ConsoleDialog::flickable() const
{
    return m_flickable;
}

QStringList ConsoleDialog::dataColors() const
{
    return m_dataColors;
}

QColor ConsoleDialog::lineColor() const
{
    return m_lineColor;
}

int ConsoleDialog::time() const
{
    return m_time;
}

int ConsoleDialog::margin() const
{
    return m_margin;
}

QColor ConsoleDialog::dropDownsTitleColor() const
{
    return m_dropDownsTitleColor;
}

QFont ConsoleDialog::dropDownsTitleFont() const
{
    return m_dropDownsTitleFont;
}

int ConsoleDialog::dataPanelHeight() const
{
    return m_dataPanelHeight;
}

int ConsoleDialog::dropDownsTitleHeight() const
{
    return m_dropDownsTitleHeight;
}

QColor ConsoleDialog::dropDownsTitleTextColor() const
{
    return m_dropDownsTitleTextColor;
}

void ConsoleDialog::generateDropDowns()
{
    if(m_portsNames.empty())
        return;

    for(const QString& portName: m_portsNames) {
        SinglePortDropDown* dropDown = new SinglePortDropDown(this);

        dropDown->setWidth(this->width());
        dropDown->setTitleColor(m_dropDownsTitleColor);
        dropDown->setTitleTextColor(m_dropDownsTitleTextColor);
        dropDown->setTitleFont(m_dropDownsTitleFont);
        dropDown->setContentColor(QColor("transparent"));
        dropDown->setContentFont(m_contentFont);
        dropDown->setTitleFrameHeight(m_dropDownsTitleHeight);
        dropDown->setContentFrameHeight(0);
        dropDown->setMargin(m_margin);
        dropDown->setDataColors(m_dataColors);
        dropDown->setDataPanelHeight(m_dataPanelHeight);
        dropDown->setLineColor(m_lineColor);
        dropDown->setTitle(portName);

        this->addItem(dropDown);
        m_ports.insert(portName, dropDown);

        connect(this, &ConsoleDialog::dropDownsTitleTextColorChanged, dropDown, &SinglePortDropDown::setTitleTextColor);
        connect(this, &ConsoleDialog::dropDownsTitleHeightChanged, dropDown, &SinglePortDropDown::setTitleFrameHeight);
        connect(this, &ConsoleDialog::dataColorsChanged, dropDown, &SinglePortDropDown::setDataColors);
        connect(this, &ConsoleDialog::contentFontChanged, dropDown, &SinglePortDropDown::setContentFont);
        connect(this, &ConsoleDialog::marginChanged, dropDown, &SinglePortDropDown::setMargin);
        connect(this, &ConsoleDialog::lineColorChanged, dropDown, &SinglePortDropDown::setLineColor);
        connect(this, &ConsoleDialog::dropDownsTitleColorChanged, dropDown, &SinglePortDropDown::setTitleColor);
        connect(this, &ConsoleDialog::dropDownsTitleFontChanged, dropDown, &SinglePortDropDown::setTitleFont);
    }
}

QQuickItem *ConsoleDialog::container()
{
    return this->container();
}

void ConsoleDialog::addMessage(QString potName, int data, int usTime)
{
    Q_ASSERT(data >= 0 && data <= 255);
    Q_ASSERT(m_portsNames.contains(potName));

    m_ports[potName]->addMessage(data, usTime);
}

void ConsoleDialog::setPortsNames(QStringList portsNames)
{
    if (m_portsNames == portsNames)
        return;

    m_portsNames = portsNames;
    emit portsNamesChanged(portsNames);
}

void ConsoleDialog::setFlickable(QQuickItem *flickable)
{
    if (m_flickable == flickable)
        return;

    m_flickable = flickable;
    emit flickableChanged(flickable);
}

void ConsoleDialog::setDataColors(QStringList dataColors)
{
    if (m_dataColors == dataColors)
        return;

    m_dataColors = dataColors;
    emit dataColorsChanged(dataColors);
}

void ConsoleDialog::setLineColor(QColor lineColor)
{
    if (m_lineColor == lineColor)
        return;

    m_lineColor = lineColor;
    emit lineColorChanged(lineColor);
}

void ConsoleDialog::setTime(int time)
{
    if (m_time == time)
        return;

    m_time = time;
    emit timeChanged(time);
}

void ConsoleDialog::setMargin(int margin)
{
    if (m_margin == margin)
        return;

    m_margin = margin;
    emit marginChanged(margin);
}

void ConsoleDialog::setDropDownsTitleColor(QColor dropDownsTitleColor)
{
    if (m_dropDownsTitleColor == dropDownsTitleColor)
        return;

    m_dropDownsTitleColor = dropDownsTitleColor;
    emit dropDownsTitleColorChanged(dropDownsTitleColor);
}

void ConsoleDialog::setDropDownsTitleFont(QFont dropDownsTitleFont)
{
    if (m_dropDownsTitleFont == dropDownsTitleFont)
        return;

    m_dropDownsTitleFont = dropDownsTitleFont;
    emit dropDownsTitleFontChanged(dropDownsTitleFont);
}

void ConsoleDialog::setDataPanelHeight(int dataPanelHeight)
{
    if (m_dataPanelHeight == dataPanelHeight)
        return;

    m_dataPanelHeight = dataPanelHeight;
    emit dataPanelHeightChanged(dataPanelHeight);
}

void ConsoleDialog::setDropDownsTitleHeight(int dropDownsTitleHeight)
{
    if (m_dropDownsTitleHeight == dropDownsTitleHeight)
        return;

    m_dropDownsTitleHeight = dropDownsTitleHeight;
    emit dropDownsTitleHeightChanged(dropDownsTitleHeight);
}

void ConsoleDialog::setDropDownsTitleTextColor(QColor dropDownsTitleTextColor)
{
    if (m_dropDownsTitleTextColor == dropDownsTitleTextColor)
        return;

    m_dropDownsTitleTextColor = dropDownsTitleTextColor;
    emit dropDownsTitleTextColorChanged(dropDownsTitleTextColor);
}

