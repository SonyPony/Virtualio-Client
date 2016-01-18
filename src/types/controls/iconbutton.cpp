#include "iconbutton.h"
#include <QPainter>
#include <QSvgRenderer>

void IconButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_enabled)
        AbstractButton::mousePressEvent(event);
}

IconButton::IconButton(QQuickItem *parent): AbstractButton(parent)
{
    m_enabled = true;
    this->setAcceptedMouseButtons(Qt::AllButtons);
    connect(this, &IconButton::enabledChanged, this, &QQuickItem::update);
}

void IconButton::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

    // stuff for painting icon
    QSvgRenderer svgRenderer;

    if(m_enabled)
        svgRenderer.load(m_iconPath);
    else
        svgRenderer.load(m_disabledIconPath);

    svgRenderer.render(painter, QRectF(QPointF(), QSizeF(this->width(), this->height())));
}

QString IconButton::iconPath() const
{
    return m_iconPath;
}

QString IconButton::disabledIconPath() const
{
    return m_disabledIconPath;
}

bool IconButton::enabled() const
{
    return m_enabled;
}

void IconButton::setIconPath(QString iconPath)
{
    if (m_iconPath == iconPath)
        return;

    m_iconPath = iconPath;
    emit iconPathChanged(iconPath);
}

void IconButton::setDisabledIconPath(QString disabledIconPath)
{
    if (m_disabledIconPath == disabledIconPath)
        return;

    m_disabledIconPath = disabledIconPath;
    emit disabledIconPathChanged(disabledIconPath);
}

void IconButton::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    m_enabled = enabled;
    emit enabledChanged(enabled);
}

