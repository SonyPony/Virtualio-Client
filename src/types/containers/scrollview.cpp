#include "scrollview.h"

ScrollView::ScrollView(QQuickItem *parent): PaintedItem(parent)
{
    m_item = NULL;
    m_horizontalScrollBar = new ScrollBar(this);
    m_verticalScrollBar = new ScrollBar(this);

    m_horizontalScrollBar->setOrientation(Qt::Horizontal);
    m_verticalScrollBar->setOrientation(Qt::Vertical);

    m_horizontalScrollBar->setColor("red");
    m_verticalScrollBar->setColor("red");

    m_horizontalScrollBar->setBackgroundColor("lime");
    m_verticalScrollBar->setBackgroundColor("lime");

    connect(this, &QQuickItem::widthChanged, [this]() {
        m_horizontalScrollBar->setWidth(this->width());
        m_verticalScrollBar->setWidth(6);
        updateHorizontalScrollbar();
    });
    
    connect(this, &QQuickItem::heightChanged, [this]() {
        m_horizontalScrollBar->setHeight(6);
        m_verticalScrollBar->setHeight(this->height());
        updateVerticalScrollbar();
    });
    
    connect(this, &QQuickItem::childrenChanged, [this]() {
        this->registerItem(this->childItems().last());
        updateVerticalScrollbar();
        updateHorizontalScrollbar();
    });

    connect(m_horizontalScrollBar, &ScrollBar::positionChanged, [this](qreal pos) {
        if(m_item == NULL)
            return;

        m_item->setX(-pos * m_item->width());
    });

    connect(m_verticalScrollBar, &ScrollBar::positionChanged, [this](qreal pos) {
        if(m_item == NULL)
            return;

        m_item->setY(-pos * m_item->height());
    });
}

void ScrollView::paint(QPainter *painter)
{

}

void ScrollView::registerItem(QQuickItem *item)
{
    disconnect(m_item, &QQuickItem::widthChanged, this, &ScrollView::updateHorizontalScrollbar);
    disconnect(m_item, &QQuickItem::heightChanged, this, &ScrollView::updateVerticalScrollbar);

    m_item = item;
    connect(m_item, &QQuickItem::widthChanged, this, &ScrollView::updateHorizontalScrollbar);
    connect(m_item, &QQuickItem::heightChanged, this, &ScrollView::updateVerticalScrollbar);
}

void ScrollView::updateVerticalScrollbar()
{
    if(m_item == NULL)
        return;
qDebug() << height() / m_item->height();
    m_verticalScrollBar->setRatio(m_item->height() / height());
}

void ScrollView::updateHorizontalScrollbar()
{
    if(m_item == NULL)
        return;
qDebug() << width() / m_item->width();
    m_horizontalScrollBar->setRatio(m_item->width() / width());
}

