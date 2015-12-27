#include "tabselectionitem.h"

void TabSelectionItem::mousePressEvent(QMouseEvent *)
{
    Q_EMIT this->selected();
}

TabSelectionItem::TabSelectionItem(QObject* parent): PaintedItem(parent)
{
}

QString TabSelectionItem::text() const
{
    return m_text;
}

QColor TabSelectionItem::textColor() const
{
    return m_textColor;
}

QFont TabSelectionItem::font() const
{
    return m_font;
}

void TabSelectionItem::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}

void TabSelectionItem::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void TabSelectionItem::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

