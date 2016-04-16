#include "infopanel.h"

#include <QTimer>

InfoPanel::InfoPanel(QQuickItem *parent)
{
    m_text = "";
    m_timer = new QTimer(this);
    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setDuration(250);

    this->setOpacity(0);

    connect(this, &InfoPanel::fontChanged, this, &QQuickItem::update);
    connect(this, &InfoPanel::textColorChanged, this, &QQuickItem::update);
    connect(this, &InfoPanel::timeoutChanged, m_timer, &QTimer::setInterval);
    connect(m_timer, &QTimer::timeout, this, &InfoPanel::hide);
}

void InfoPanel::paint(QPainter *painter)
{
    // draw background
    painter->setBrush(m_color);
    painter->setPen(m_color);

    const double width = this->width();
    const double height = this->height();

    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(width, 0);
    path.lineTo(width - height, height);
    path.lineTo(height, height);
    path.lineTo(0, 0);

    painter->drawPath(path);

    // draw text
    painter->setPen(m_textColor);
    painter->setBrush(m_textColor);
    painter->setFont(m_font);
    painter->drawText(this->boundingRect(), m_text, QTextOption(Qt::AlignCenter));
}

QFont InfoPanel::font() const
{
    return m_font;
}

QColor InfoPanel::textColor() const
{
    return m_textColor;
}

int InfoPanel::timeout() const
{
    return m_timeout;
}

void InfoPanel::hide()
{
    if(m_opacityAnimation->state() == QPropertyAnimation::Running)
        m_opacityAnimation->stop();
    m_opacityAnimation->setEndValue(0);
    m_opacityAnimation->start();
}

void InfoPanel::show(QString text)
{
    m_text = text;
    this->update();

    if(m_opacityAnimation->state() == QPropertyAnimation::Running)
        m_opacityAnimation->stop();
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->start();
    m_timer->start();
}

void InfoPanel::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void InfoPanel::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void InfoPanel::setTimeout(int timeout)
{
    if (m_timeout == timeout)
        return;

    m_timeout = timeout;
    emit timeoutChanged(timeout);
}
