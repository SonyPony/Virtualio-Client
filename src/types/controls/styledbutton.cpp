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

StyledButton::StyledButton(QQuickItem *parent): AbstractButton(parent)
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
}

void StyledButton::paint(QPainter *painter)
{
    QTextOption textOption;
    textOption.setAlignment(Qt::AlignCenter);

    painter->setRenderHints(QPainter::Antialiasing);

    if(m_hovered)
        painter->setCompositionMode(QPainter::CompositionMode_SourceOut);

    else
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter->setFont(m_font);
    painter->setPen(m_textColor);
    painter->drawText(boundingRect(), m_text, textOption);

    painter->setPen(QPen(m_color, 1));
    painter->drawRect(boundingRect().adjusted(1, 1, -1, -1));

    painter->setPen("transparent");
    painter->setBrush(m_backgroundColor);
    painter->drawRect(boundingRect());

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
