#include "textbutton.h"

TextButton::TextButton(QQuickItem *parent) : AbstractButton(parent)
{
    m_text = "";
    m_font = QFont();
}

QFont TextButton::font() const
{
    return m_font;
}

QColor TextButton::textColor() const
{
    return m_textColor;
}

QString TextButton::text() const
{
    return m_text;
}

void TextButton::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void TextButton::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void TextButton::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}


