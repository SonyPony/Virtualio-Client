#include "abstractbutton.h"

void AbstractButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_pressed = true;
}

void AbstractButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(boundingRect().contains(event->pos()) && m_pressed)
        emit clicked(event->pos());
    m_pressed = false;
}

void AbstractButton::hoverEnterEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;

    Q_EMIT entered();
}

void AbstractButton::hoverLeaveEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;

    Q_EMIT leaved();
}

AbstractButton::AbstractButton(QQuickItem *parent): PaintedItem(parent)
{
    m_pressed = false;
    m_hovered = false;
    m_text = "";
    m_font = QFont();

    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
}

QFont AbstractButton::font() const
{
    return m_font;
}

QColor AbstractButton::textColor() const
{
    return m_textColor;
}

QString AbstractButton::text() const
{
    return m_text;
}

void AbstractButton::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void AbstractButton::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void AbstractButton::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}


