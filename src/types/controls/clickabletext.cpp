#include "clickabletext.h"
#include <QFontMetrics>
#include <qmath.h>

ClickableText::ClickableText(QQuickItem *parent): TextButton(parent)
{
    m_showDescription = false;
    p_backgroundColor = QColor("transparent");
    m_backgroundAnimation = new QPropertyAnimation(this, "_backgroundColor", this);
    m_backgroundAnimation->setDuration(350);
    m_backgroundAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_margins = 0;
    m_description = "";
    setAcceptHoverEvents(true);

    connect(this, &ClickableText::showDescriptionChanged, this, &ClickableText::resizeAccordingText);
    connect(this, &ClickableText::marginsChanged, this, &ClickableText::resizeAccordingText);
    connect(this, &ClickableText::textChanged, this, &ClickableText::resizeAccordingText);
    connect(this, &ClickableText::descriptionChanged, this, &ClickableText::resizeAccordingText);

    // need to use QQuickItem::update
    connect(this, &ClickableText::entered, this, &QQuickItem::update);
    connect(this, &ClickableText::leaved, this, &QQuickItem::update);
    connect(this, &ClickableText::_backgroundColorChanged, this, &QQuickItem::update);

    connect(this, &ClickableText::entered, this, &ClickableText::showBackGround);
    connect(this, &ClickableText::leaved, this, &ClickableText::hideBackground);

    // set pixel size a ccording to height
    connect(this, &ClickableText::heightChanged, [this]() {
        if(m_showDescription)
            m_font.setPixelSize(this->height() / 2.25);
        else {
            m_font.setPixelSize(this->height());
            // need to change pixel size according to font height
            m_font.setPixelSize(qPow(this->height(), 2) / (double)QFontMetrics(m_font).height());
        }
        resizeAccordingText();
    });
}

ClickableText::~ClickableText()
{
    delete m_backgroundAnimation;
}

void ClickableText::paint(QPainter *painter)
{
    // draw background
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter->setPen(QColor("transparent"));
    painter->setBrush(p_backgroundColor);
    painter->drawRect(boundingRect().adjusted(1, 1, -1, -1));

    // reset underline
    m_font.setUnderline(false);
    painter->setFont(m_font);
    painter->setBrush(m_color);

    // draw description
    if(m_showDescription) {
        painter->setPen(m_descriptionColor);
        painter->drawText(boundingRect().adjusted(m_margins, 0, 0, 0), Qt::AlignBottom, m_description);
    }

    // underline if is hovered
    if(m_hovered) {
        m_font.setUnderline(true);
        painter->setFont(m_font);
    }

    // draw title text
    painter->setPen(m_color);
    painter->drawText(boundingRect().adjusted(m_margins, 0, 0, 0), Qt::AlignTop, m_text);
}

QString ClickableText::description() const
{
    return m_description;
}

QColor ClickableText::descriptionColor() const
{
    return m_descriptionColor;
}

QColor ClickableText::backgroundColor() const
{
    return m_backgroundColor;
}

QColor ClickableText::_backgroundColor() const
{
    return p_backgroundColor;
}

int ClickableText::margins() const
{
    return m_margins;
}

bool ClickableText::showDescription() const
{
    return m_showDescription;
}

void ClickableText::hideBackground()
{
    if(m_backgroundAnimation->state() == QAbstractAnimation::Running)
        m_backgroundAnimation->setCurrentTime(m_backgroundAnimation->duration());   // end animation

    m_backgroundAnimation->setStartValue(m_backgroundColor);
    m_backgroundAnimation->setEndValue(QColor("transparent"));
    m_backgroundAnimation->start();
}

void ClickableText::showBackGround()
{
    if(m_backgroundAnimation->state() == QAbstractAnimation::Running)
        m_backgroundAnimation->setCurrentTime(m_backgroundAnimation->duration());   // end animation

    m_backgroundAnimation->setStartValue(QColor("transparent"));
    m_backgroundAnimation->setEndValue(m_backgroundColor);
    m_backgroundAnimation->start();
}

void ClickableText::resizeAccordingText()
{
    QFontMetrics fm(m_font);

    if(m_showDescription)
        setWidth(qMax(fm.width(m_text), fm.width(m_description)) + 2 * m_margins);
    else
        setWidth(fm.width(m_text) + 2* m_margins);
}

void ClickableText::setDescription(QString description)
{
    if (m_description == description)
        return;

    m_description = description;
    emit descriptionChanged(description);
}

void ClickableText::setDescriptionColor(QColor descriptionColor)
{
    if (m_descriptionColor == descriptionColor)
        return;

    m_descriptionColor = descriptionColor;
    emit descriptionColorChanged(descriptionColor);
}

void ClickableText::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(backgroundColor);
}

void ClickableText::set_backgroundColor(QColor _backgroundColor)
{
    if (p_backgroundColor == _backgroundColor)
        return;

    p_backgroundColor = _backgroundColor;
    emit _backgroundColorChanged(_backgroundColor);
}

void ClickableText::setMargins(int margins)
{
    if (m_margins == margins)
        return;

    m_margins = margins;
    emit marginsChanged(margins);
}

void ClickableText::setShowDescription(bool showDescription)
{
    if (m_showDescription == showDescription)
        return;

    m_showDescription = showDescription;
    emit showDescriptionChanged(showDescription);
}

