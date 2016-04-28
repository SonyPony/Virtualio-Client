#include "styledbutton.h"
#include <QPainter>

void StyledButton::hoverEnterEvent(QHoverEvent *event)
{
    AbstractButton::hoverEnterEvent(event);
    invertColors();
}

void StyledButton::hoverLeaveEvent(QHoverEvent *event)
{
    AbstractButton::hoverLeaveEvent(event);
    invertColors();
}

StyledButton::StyledButton(QQuickItem *parent): TextButton(parent)
{
    m_backgroundColor = "transparent";

    m_backgroundColorAnimation = new QPropertyAnimation(this, "_backgroundColor", this);
    m_colorAnimation = new QPropertyAnimation(this, "color", this);
    m_textColorAnimation = new QPropertyAnimation(this, "textColor", this);
    m_backgroundColorAnimation->setDuration(400);
    m_colorAnimation->setDuration(400);
    m_textColorAnimation->setDuration(400);

    m_hoverAnimation = new QParallelAnimationGroup(this);
    m_hoverAnimation->addAnimation(m_backgroundColorAnimation);
    m_hoverAnimation->addAnimation(m_colorAnimation);
    m_hoverAnimation->addAnimation(m_textColorAnimation);

    connect(this, SIGNAL(_backgroundColorChanged(QColor)), this, SLOT(update()));
    connect(this, SIGNAL(colorChanged(QColor)), this, SLOT(update()));
    connect(this, SIGNAL(textColorChanged(QColor)), this, SLOT(update()));
    connect(this, &StyledButton::borderColorChanged, this, &QQuickItem::update);
    connect(this, &StyledButton::colorChanged, this, &QQuickItem::update);
    connect(this, &StyledButton::fontChanged, this, &QQuickItem::update);
}

void StyledButton::paint(QPainter *painter)
{
    //painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->setBrush(QColor("transparent"));
    painter->setPen(QPen(m_borderColor, 1));
    painter->drawRect(boundingRect().adjusted(1, 1, -1, -1));

    if(m_hovered)
        painter->setCompositionMode(QPainter::CompositionMode_SourceOut);

    else
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter->setFont(m_font);
    painter->setPen(m_textColor);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_text);

    painter->setPen(QColor("transparent"));
    painter->setBrush(m_backgroundColor);
    painter->drawRect(boundingRect().adjusted(1, 1, -1, -1));
}

QColor StyledButton::_backgroundColor() const
{
    return m_backgroundColor;
}

void StyledButton::invertColors()
{
    m_hoverAnimation->setCurrentTime(m_colorAnimation->duration());

    m_colorAnimation->setEndValue(m_textColor);
    m_textColorAnimation->setEndValue(m_color);

    if(m_hovered)
        m_backgroundColorAnimation->setEndValue(m_textColor);
    else
        m_backgroundColorAnimation->setEndValue(QColor("transparent"));

    m_hoverAnimation->start();
}

void StyledButton::_setBackgroundColor(QColor _backgroundColor)
{
    if (m_backgroundColor == _backgroundColor)
        return;

    m_backgroundColor = _backgroundColor;
    emit _backgroundColorChanged(_backgroundColor);
}

void StyledButton::setBorderColor(QColor borderColor)
{
    if (m_borderColor == borderColor)
        return;

    m_borderColor = borderColor;
    emit borderColorChanged(borderColor);
}

QColor StyledButton::borderColor() const
{
    return m_borderColor;
}
