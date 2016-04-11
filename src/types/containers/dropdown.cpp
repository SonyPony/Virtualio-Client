#include "dropdown.h"
#include <QPainter>

qreal DropDown::currentY() const
{
    return m_currentY;
}

DropDown::DropDown(QQuickItem *parent): HideableWidget(parent)
{
    m_currentY = 0;
}

void DropDown::paint(QPainter *painter)
{
    HideableWidget::paint(painter);
}

void DropDown::resetY()
{
    m_currentY = 0;
}

QQuickItem* DropDown::addItem(QQuickItem *item)
{
    item->setY(m_currentY);
    item->setWidth(this->width());
    m_currentY += item->height();

    // anchor to previous item
    // contains container
    if(!this->container()->childItems().isEmpty()){
        QQuickItem* previousItem = this->container()->childItems().last();

        connect(previousItem, &QQuickItem::yChanged, [previousItem, item]() {
            item->setY(previousItem->y() + previousItem->height());
        });
        connect(previousItem, &QQuickItem::heightChanged, [previousItem, item]() {
            item->setY(previousItem->y() + previousItem->height());
        });
    }

    connect(this, &DropDown::widthChanged, [this, item]() { item->setWidth(this->width()); });
    connect(item, &QQuickItem::heightChanged, [this]() {
        m_currentY = 0;
        for(const QQuickItem* child: this->container()->childItems())
            m_currentY += child->height();

        this->container()->setHeight(m_currentY);
    });

    item->setParentItem(this->container());

    return item;
}

