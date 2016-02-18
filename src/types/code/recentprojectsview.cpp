#include "recentprojectsview.h"

RecentProjectsView::RecentProjectsView(QQuickItem *parent): PaintedItem(parent)
{
    connect(this, &RecentProjectsView::titleColorChanged, this, &QQuickItem::update);
    connect(this, &RecentProjectsView::fontChanged, this, &QQuickItem::update);
}

void RecentProjectsView::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    painter->setFont(m_font);
    painter->setBrush(m_color);
    painter->setPen(m_color);

    painter->drawRect(this->boundingRect());

    QRectF rect = this->boundingRect();
    rect.setLeft(m_font.pixelSize() / 2.);
    rect.setTop(m_font.pixelSize() / 2.);
    painter->setPen(m_titleColor);
    painter->setBrush(m_titleColor);
    painter->drawText(rect, Qt::AlignTop | Qt::AlignLeft, tr("Recent projects"));
}

void RecentProjectsView::registerType()
{
    qmlRegisterType<RecentProjectsView>("RecentProjectsView", 1, 0, "RecentProjectsView");
}

QColor RecentProjectsView::titleColor() const
{
    return m_titleColor;
}

QFont RecentProjectsView::font() const
{
    return m_font;
}

void RecentProjectsView::setTitleColor(QColor titleColor)
{
    if (m_titleColor == titleColor)
        return;

    m_titleColor = titleColor;
    emit titleColorChanged(titleColor);
}

void RecentProjectsView::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

