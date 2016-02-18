#include "moduleconnectionpanel.h"

ModuleConnectionPanel::ModuleConnectionPanel(QQuickItem *parent): PaintedItem(parent)
{
    m_color = QColor("transparent");
    m_colorAnimation = new QPropertyAnimation(this, "__stateColor", this);
    m_colorAnimation->setDuration(400);
    m_textAnimation = new TextChangeAnimation(this);
    m_textAnimation->setTarget(this);
    m_textAnimation->setDuration(m_colorAnimation->duration());
    m_textAnimation->setStartText(tr("Disconnected"));
    m_textAnimation->setEndText(tr("Connected"));

    connect(this, &ModuleConnectionPanel::connectionStateChanged, this, &ModuleConnectionPanel::startTextAnimation);
    connect(this, &ModuleConnectionPanel::connectionStateChanged, this, &ModuleConnectionPanel::startColorAnimation);
    connect(this, &ModuleConnectionPanel::inactiveColorChanged, this, &ModuleConnectionPanel::__setStateColor);
    connect(this, &ModuleConnectionPanel::__stateColorChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::connectionStateChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::widthChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::heightChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::fontChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::activeColorChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::inactiveColorChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::colorChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::connectionStatePosChanged, this, &QQuickItem::update);
    connect(this, &ModuleConnectionPanel::moduleNameChanged, this, &QQuickItem::update);
}

void ModuleConnectionPanel::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(this->boundingRect());

    painter->setFont(m_font);

    // connection state
    QRectF rect = this->boundingRect();
    rect.setLeft(m_connectionStatePos);

    painter->setPen(p_stateColor);
    painter->setOpacity(m_textAnimation->textOpacity());
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, m_textAnimation->currentText());

    // draw connection status icon
    QPen pen(p_stateColor, 2);
    const double radius = ((this->height() - pen.width()) / 2.) / 2.5;

    painter->setOpacity(1);
    painter->setPen(pen);
    painter->drawEllipse(QPointF(radius + pen.width(), this->height() / 2.), radius, radius);

    rect = this->boundingRect();
    rect.setLeft(radius * 4.);

    // draw module name
    painter->setPen(m_nameColor);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, m_moduleName);
    // draw split line
    painter->drawLine(m_connectionStatePos - 15, 0, m_connectionStatePos - 15, this->height());
}

QFont ModuleConnectionPanel::font() const
{
    return m_font;
}

QColor ModuleConnectionPanel::activeColor() const
{
    return m_activeColor;
}

QColor ModuleConnectionPanel::inactiveColor() const
{
    return m_inactiveColor;
}

QString ModuleConnectionPanel::moduleName() const
{
    return m_moduleName;
}

int ModuleConnectionPanel::connectionStatePos() const
{
    return m_connectionStatePos;
}

int ModuleConnectionPanel::connectionState() const
{
    return m_connectionState;
}

QColor ModuleConnectionPanel::__stateColor() const
{
    return p_stateColor;
}

QColor ModuleConnectionPanel::nameColor() const
{
    return m_nameColor;
}

void ModuleConnectionPanel::startTextAnimation(int newConnectionState)
{
    m_textAnimation->stop();

    if(newConnectionState == ModuleState::Connected) {
        m_textAnimation->setStartText(tr("Disconnected"));
        m_textAnimation->setEndText(tr("Connected"));
    }

    else {
        m_textAnimation->setStartText(tr("Connected"));
        m_textAnimation->setEndText(tr("Disconnected"));
    }

    m_textAnimation->start();
}

void ModuleConnectionPanel::startColorAnimation(int newConnectionState)
{
    m_colorAnimation->stop();
    m_colorAnimation->setStartValue(p_stateColor);

    if(newConnectionState == ModuleState::Connected)
        m_colorAnimation->setEndValue(m_activeColor);
    else
        m_colorAnimation->setEndValue(m_inactiveColor);

    m_colorAnimation->start();
}

void ModuleConnectionPanel::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void ModuleConnectionPanel::setActiveColor(QColor activeColor)
{
    if (m_activeColor == activeColor)
        return;

    m_activeColor = activeColor;
    emit activeColorChanged(activeColor);
}

void ModuleConnectionPanel::setInactiveColor(QColor inactiveColor)
{
    if (m_inactiveColor == inactiveColor)
        return;

    m_inactiveColor = inactiveColor;
    emit inactiveColorChanged(inactiveColor);
}

void ModuleConnectionPanel::setModuleName(QString moduleName)
{
    if (m_moduleName == moduleName)
        return;

    m_moduleName = moduleName;
    emit moduleNameChanged(moduleName);
}

void ModuleConnectionPanel::setConnectionStatePos(int connectionStatePos)
{
    if (m_connectionStatePos == connectionStatePos)
        return;

    m_connectionStatePos = connectionStatePos;
    emit connectionStatePosChanged(connectionStatePos);
}

void ModuleConnectionPanel::setConnectionState(int connectionState)
{
    if (m_connectionState == connectionState)
        return;

    m_connectionState = connectionState;
    emit connectionStateChanged(connectionState);
}

void ModuleConnectionPanel::__setStateColor(QColor __stateColor)
{
    if (p_stateColor == __stateColor)
        return;

    p_stateColor = __stateColor;
    emit __stateColorChanged(__stateColor);
}

void ModuleConnectionPanel::setNameColor(QColor nameColor)
{
    if (m_nameColor == nameColor)
        return;

    m_nameColor = nameColor;
    emit nameColorChanged(nameColor);
}

