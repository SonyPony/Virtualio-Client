#include "tagmenuselectionitem.h"

void TagMenuSelectionItem::init()
{
    m_textColorAnimation = new QPropertyAnimation(this, "__textColor", this);
    m_textColorAnimation->setDuration(350);
    m_textColorAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);

    connect(this, &TagMenuSelectionItem::__textColorChanged, this, &QQuickItem::update);
    connect(this, &TagMenuSelectionItem::hoveredChanged, this, &TagMenuSelectionItem::invertTextColors);
    connect(this, &TagMenuSelectionItem::defaultColorChanged, this, &TagMenuSelectionItem::__setTextColor);
    connect(this, &TagMenuSelectionItem::selected, [this]() {
        m_selected = true;
        this->update();
    });
    connect(this, &TagMenuSelectionItem::disSelected, [this]() {
        m_selected = false;
        this->update();
    });
}

void TagMenuSelectionItem::invertTextColors(bool hovered)
{
    m_textColorAnimation->setCurrentTime(m_textColorAnimation->duration());

    if(hovered)
        m_textColorAnimation->setEndValue(m_textColor);
    else
        m_textColorAnimation->setEndValue(m_defaultColor);
    m_textColorAnimation->start();
}

void TagMenuSelectionItem::hoverEnterEvent(QHoverEvent *)
{
    Q_EMIT this->hoveredChanged(true);
}

void TagMenuSelectionItem::hoverLeaveEvent(QHoverEvent *)
{
    Q_EMIT this->hoveredChanged(false);
}

TagMenuSelectionItem::TagMenuSelectionItem(QObject *parent) : TabSelectionItem(parent)
{
    this->init();
}

TagMenuSelectionItem::TagMenuSelectionItem(QString text, QColor color, QColor defaultColor, QObject *parent): TabSelectionItem(parent)
{
    m_text = text;
    m_textColor = color;
    m_defaultColor = defaultColor;
    p_textColor = defaultColor;

    this->init();
}

void TagMenuSelectionItem::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    // draw background
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(this->boundingRect());

    // draw text
    QColor color;
    if(m_selected)
        color = m_textColor;
    else
        color = p_textColor;

    painter->setBrush(color);
    painter->setPen(QPen(color));

    painter->setFont(m_font);
    painter->drawText(boundingRect(), m_text, QTextOption(Qt::AlignCenter));
}

QColor TagMenuSelectionItem::defaultColor() const
{
    return m_defaultColor;
}

QColor TagMenuSelectionItem::__textColor() const
{
    return p_textColor;
}

void TagMenuSelectionItem::setDefaultColor(QColor defaultColor)
{
    if (m_defaultColor == defaultColor)
        return;

    m_defaultColor = defaultColor;
    emit defaultColorChanged(defaultColor);
}

void TagMenuSelectionItem::__setTextColor(QColor __textColor)
{
    if (p_textColor == __textColor)
        return;

    p_textColor = __textColor;
    emit __textColorChanged(__textColor);
}

