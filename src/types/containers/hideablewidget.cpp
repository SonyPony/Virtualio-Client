#include "hideablewidget.h"
#include <QPainter>

void HideableWidget::mousePressEvent(QMouseEvent *e)
{
    QRect rect(0, 0, this->width(), m_titleFrameHeight);

    if(rect.contains(e->pos())) {
        if(m_hidden)
            this->show();
        else
            this->hide();
        this->update();
    }
}

HideableWidget::HideableWidget(QQuickItem *parent): PaintedItem(parent)
{
    m_resizeAnimation = new  QPropertyAnimation(this, "height", this);
    m_resizeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_resizeAnimation->setDuration(400);
    m_hidden = false;
    m_titleFrameHeight = 0;
    m_contentFrameHeight = 0;
    m_container = new QQuickItem(this);
    m_container->setClip(true);
    m_contentColor = QColor("transparent");

    this->setClip(true);
    this->setHeight(0);
    this->setAcceptedMouseButtons(Qt::LeftButton);

    connect(this, &HideableWidget::titleFrameHeightChanged, this, &HideableWidget::resize);
    connect(this, &HideableWidget::contentFrameHeightChanged, this, &HideableWidget::resize);
    connect(this, &HideableWidget::heightChanged, this, &QQuickItem::update);
    connect(this, &HideableWidget::titleChanged, this, &QQuickItem::update);
    connect(this, &HideableWidget::titleColorChanged, this, &QQuickItem::update);
    connect(this, &HideableWidget::contentColorChanged, this, &QQuickItem::update);
    connect(this, &HideableWidget::contentFrameHeightChanged, m_container, &QQuickItem::setHeight);
    connect(this, &HideableWidget::titleFrameHeightChanged, m_container, &QQuickItem::setY);
    connect(this, &HideableWidget::widthChanged, [this]() { m_container->setWidth(this->width()); });
    connect(m_container, &QQuickItem::widthChanged, [this]() {
        this->setContainerWidth(m_container->width());
    });
    connect(m_container, &QQuickItem::heightChanged, [this]() {
        this->setContainerHeight(m_container->height());
    });
}

void HideableWidget::paint(QPainter *painter)
{
    const int width = this->width();

    // draw title
    painter->setBrush(m_titleColor);
    painter->setPen(m_titleColor);

    painter->drawRect(0, 0, width, m_titleFrameHeight);

    // draw content
    painter->setBrush(m_contentColor);
    painter->setPen(m_contentColor);

    painter->drawRect(0, m_titleFrameHeight, width, m_contentFrameHeight);
}

void HideableWidget::hide()
{
    if(m_resizeAnimation->state() == QPropertyAnimation::Running)
        m_resizeAnimation->stop();

    m_hidden = true;
    m_resizeAnimation->setStartValue(this->height());
    m_resizeAnimation->setEndValue(m_titleFrameHeight);
    m_resizeAnimation->start();

    Q_EMIT this->hided();
}

void HideableWidget::show()
{
    if(m_resizeAnimation->state() == QPropertyAnimation::Running)
        m_resizeAnimation->stop();

    m_hidden = false;
    m_resizeAnimation->setStartValue(this->height());
    m_resizeAnimation->setEndValue(m_titleFrameHeight + m_contentFrameHeight);
    m_resizeAnimation->start();

    Q_EMIT this->showed();
}

void HideableWidget::unbindRepositioningContainer()
{
    m_container->setY(0);
    disconnect(this, &HideableWidget::titleFrameHeightChanged, m_container, &QQuickItem::setY);
}

void HideableWidget::setContainerParent(QQuickItem *parent)
{
    m_container->setParentItem(parent);
}

qreal HideableWidget::titleFrameHeight() const
{
    return m_titleFrameHeight;
}

qreal HideableWidget::contentFrameHeight() const
{
    return m_contentFrameHeight;
}

QColor HideableWidget::titleColor() const
{
    return m_titleColor;
}

QColor HideableWidget::titleTextColor() const
{
    return m_titleTextColor;
}

QFont HideableWidget::titleFont() const
{
    return m_titleFont;
}

QFont HideableWidget::contentFont() const
{
    return m_contentFont;
}

QColor HideableWidget::contentColor() const
{
    return m_contentColor;
}

QQuickItem *HideableWidget::container()
{
    return m_container;
}

int HideableWidget::containerWidth() const
{
    return m_containerWidth;
}

int HideableWidget::containerHeight() const
{
    return m_containerHeight;
}

QString HideableWidget::title() const
{
    return m_title;
}

void HideableWidget::resize()
{
    if(m_hidden)
        this->setHeight(m_titleFrameHeight);
    else
        this->setHeight(m_titleFrameHeight + m_contentFrameHeight);
}

void HideableWidget::setContainerWidth(int containerWidth)
{
    if (m_containerWidth == containerWidth)
        return;

    m_containerWidth = containerWidth;
    emit containerWidthChanged(containerWidth);
}

void HideableWidget::setContainerHeight(int containerHeight)
{
    if (m_containerHeight == containerHeight)
        return;

    m_containerHeight = containerHeight;
    emit containerHeightChanged(containerHeight);
}

void HideableWidget::setTitleFrameHeight(qreal titleFrameHeight)
{
    if (m_titleFrameHeight == titleFrameHeight)
        return;

    m_titleFrameHeight = titleFrameHeight;
    emit titleFrameHeightChanged(titleFrameHeight);
}

void HideableWidget::setContentFrameHeight(qreal contentFrameHeight)
{
    if (m_contentFrameHeight == contentFrameHeight)
        return;

    m_contentFrameHeight = contentFrameHeight;
    emit contentFrameHeightChanged(contentFrameHeight);
}

void HideableWidget::setTitleColor(QColor titleColor)
{
    if (m_titleColor == titleColor)
        return;

    m_titleColor = titleColor;
    emit titleColorChanged(titleColor);
}

void HideableWidget::setTitleTextColor(QColor titleTextColor)
{
    if (m_titleTextColor == titleTextColor)
        return;

    m_titleTextColor = titleTextColor;
    emit titleTextColorChanged(titleTextColor);
}

void HideableWidget::setTitleFont(QFont titleFont)
{
    if (m_titleFont == titleFont)
        return;

    m_titleFont = titleFont;
    emit titleFontChanged(titleFont);
}

void HideableWidget::setContentFont(QFont contentFont)
{
    if (m_contentFont == contentFont)
        return;

    m_contentFont = contentFont;
    emit contentFontChanged(contentFont);
}

void HideableWidget::setContentColor(QColor contentColor)
{
    if (m_contentColor == contentColor)
        return;

    m_contentColor = contentColor;
    emit contentColorChanged(contentColor);
}

void HideableWidget::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(title);
}

