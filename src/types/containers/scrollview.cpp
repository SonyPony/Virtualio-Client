#include "scrollview.h"

ScrollView::ScrollView(QQuickItem *parent): PaintedItem(parent)
{
    m_item = NULL;
    m_horizontalScrollBar = new ScrollBar(this);
    m_verticalScrollBar = new ScrollBar(this);

    m_horizontalScrollBar->setOrientation(Qt::Horizontal);
    m_verticalScrollBar->setOrientation(Qt::Vertical);

    m_horizontalScrollBar->setZ(1);
    m_verticalScrollBar->setZ(1);

    setClip(true);

    connect(this, &ScrollView::widthChanged, this, &ScrollView::checkIfHideScrollBars);
    connect(this, &ScrollView::heightChanged, this, &ScrollView::checkIfHideScrollBars);
    // set colors
    connect(this, &ScrollView::colorChanged, m_verticalScrollBar, &ScrollBar::setColor);
    connect(this, &ScrollView::colorChanged, m_horizontalScrollBar, &ScrollBar::setColor);
    connect(this, &ScrollView::backgroundColorChanged, m_horizontalScrollBar, &ScrollBar::setBackgroundColor);
    connect(this, &ScrollView::backgroundColorChanged, m_verticalScrollBar, &ScrollBar::setBackgroundColor);

    // update scrollbar size
    connect(this, &ScrollView::widthChanged, [this]() {
        m_horizontalScrollBar->setWidth(this->width());
        m_verticalScrollBar->setWidth(6);
        updateHorizontalScrollbar();
    });
    
    // update scrollbar size
    connect(this, &ScrollView::heightChanged, [this]() {
        m_horizontalScrollBar->setHeight(6);
        m_verticalScrollBar->setHeight(this->height());
        updateVerticalScrollbar();
    });
    
    // register last children, because scrollbars are first 2 childrens
    connect(this, &ScrollView::childrenChanged, [this]() {
        this->registerItem(this->childItems().last());
        updateVerticalScrollbar();
        updateHorizontalScrollbar();
    });

    // move horizontally
    connect(m_horizontalScrollBar, &ScrollBar::positionChanged, [this](qreal pos) {
        if(m_item == NULL)
            return;

        m_item->setX(-pos * m_item->width());
    });

    // move vertically
    connect(m_verticalScrollBar, &ScrollBar::positionChanged, [this](qreal pos) {
        if(m_item == NULL)
            return;

        m_item->setY(-pos * m_item->height());
    });
}

void ScrollView::paint(QPainter *painter)
{

}

QColor ScrollView::backgroundColor() const
{
    return m_backgroundColor;
}

void ScrollView::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    Q_EMIT backgroundColorChanged(backgroundColor);
}

void ScrollView::checkIfHideScrollBars()
{
    if(m_item == NULL)
        return;

    if(width() >= m_item->width())  // if scrollview is bigger than item, then hide scrollbars
        m_horizontalScrollBar->setOpacity(0);
    else if(!m_horizontalScrollBar->opacity())  // otherwise hide if is hidden
        m_horizontalScrollBar->setOpacity(1);

    if(height() >= m_item->height())  // if scrollview is bigger than item, then hide scrollbars
        m_verticalScrollBar->setOpacity(0);
    else if(!m_verticalScrollBar->opacity())  // otherwise hide if is hidden
        m_verticalScrollBar->setOpacity(1);
}

void ScrollView::registerItem(QQuickItem *item)
{
    if(m_item) {
        disconnect(m_item, &QQuickItem::widthChanged, this, &ScrollView::updateHorizontalScrollbar);
        disconnect(m_item, &QQuickItem::heightChanged, this, &ScrollView::updateVerticalScrollbar);
    }

    m_item = item;
    connect(m_item, &QQuickItem::widthChanged, this, &ScrollView::updateHorizontalScrollbar);
    connect(m_item, &QQuickItem::heightChanged, this, &ScrollView::updateVerticalScrollbar);
}

void ScrollView::updateVerticalScrollbar()
{
    if(m_item == NULL || height() == 0)
        return;

    m_verticalScrollBar->setRatio(m_item->height() / height());
}

void ScrollView::updateHorizontalScrollbar()
{
    if(m_item == NULL || width() == 0)
        return;

    m_horizontalScrollBar->setRatio(m_item->width() / width());
}

