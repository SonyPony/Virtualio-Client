#include "scrollbar.h"
#include <QSize>
#include <QPoint>
#include "interval.h"

void ScrollBar::mousePressEvent(QMouseEvent *e)
{
    // need event pos to be related to m_nonInteractiveScrollbar
    QPoint diffPoint;
    if(m_orientation == Qt::Horizontal)
        diffPoint.setX(e->x() - m_nonInteractiveScrollBar->x());
    else
        diffPoint.setY(e->y() - m_nonInteractiveScrollBar->y());

    m_dragAndDropManager->pressed(diffPoint);
}

void ScrollBar::mouseMoveEvent(QMouseEvent *e)
{
    // need event pos to be related to m_nonInteractiveScrollbar
    QPoint diffPoint;
    if(m_orientation == Qt::Horizontal)
        diffPoint.setX(e->x() - m_nonInteractiveScrollBar->x());
    else
        diffPoint.setY(e->y() - m_nonInteractiveScrollBar->y());

    // check wheter noninteractiveScrollBar is not out of range ScrollBar area
    const QSize distanceFromTL = m_dragAndDropManager->distanceFromTLCorner();
    int difference;
    Interval moveArea;

    // calculate interval of positions where X can move
    if(m_orientation == Qt::Horizontal) {
        difference = diffPoint.x() - distanceFromTL.width();
        moveArea.setMax(this->width() - m_nonInteractiveScrollBar->width());
    }

    // calculate interval of positions where Y can move
    else {
        difference = diffPoint.y() - distanceFromTL.height();
        moveArea.setMax(this->height() - m_nonInteractiveScrollBar->height());
    }

    if(!moveArea.isIn(m_nonInteractiveScrollBar->position() + difference)) {
        if(m_orientation == Qt::Horizontal)
            diffPoint.setX(-m_nonInteractiveScrollBar->x() + distanceFromTL.width());
        else
            diffPoint.setY(-m_nonInteractiveScrollBar->y() + distanceFromTL.height());

        if(difference > 0) {
            if(m_orientation == Qt::Horizontal)
                diffPoint.rx() += width() - m_nonInteractiveScrollBar->width();
            else
                diffPoint.ry() += height() - m_nonInteractiveScrollBar->height();
        }
    }

    m_dragAndDropManager->move(diffPoint);
}

void ScrollBar::mouseReleaseEvent(QMouseEvent *e)
{
    m_dragAndDropManager->released();
}

ScrollBar::ScrollBar(QQuickItem *parent): PaintedItem(parent), m_ratio(1)
{
    m_nonInteractiveScrollBar = new NonInteractiveScrollBar(this);
    m_nonInteractiveScrollBar->setOrientation(Qt::Horizontal);
    m_dragAndDropManager = new DragAndDropManager(m_nonInteractiveScrollBar, this);
    m_dragAndDropManager->setEnabledOrientations(Qt::Horizontal);

    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &ScrollBar::ratioChanged, this, &ScrollBar::updateScrollBarSize);
    connect(this, &QQuickItem::widthChanged, this, &ScrollBar::updateScrollBarSize);
    connect(this, &QQuickItem::heightChanged, this, &ScrollBar::updateScrollBarSize);

    connect(this, &ScrollBar::orientationChanged, [this](int orientation) {
        this->m_dragAndDropManager->setEnabledOrientations(orientation);
        this->m_nonInteractiveScrollBar->setOrientation(orientation);
    });

    connect(this, &PaintedItem::colorChanged, [this](QColor color) {
        this->m_nonInteractiveScrollBar->setColor(color);
    });
}

void ScrollBar::paint(QPainter *painter)
{
    painter->setBrush(m_backgroundColor);
    painter->drawRect(boundingRect());
}

QColor ScrollBar::backgroundColor() const
{
    return m_backgroundColor;
}

double ScrollBar::ratio() const
{
    return m_ratio;
}

int ScrollBar::orientation() const
{
    return m_orientation;
}

void ScrollBar::updateScrollBarSize()
{
    if(this->m_orientation == Qt::Horizontal) {
        m_nonInteractiveScrollBar->setHeight(height());
        if(m_ratio)
            m_nonInteractiveScrollBar->setWidth(width() / m_ratio);
    }

    else {
        m_nonInteractiveScrollBar->setWidth(width());
        if(m_ratio)
            m_nonInteractiveScrollBar->setHeight(height() / m_ratio);
    }
}

void ScrollBar::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(backgroundColor);
}

void ScrollBar::setRatio(double ratio)
{
    Q_ASSERT(ratio);

    if (m_ratio == ratio)
        return;

    m_ratio = ratio;
    emit ratioChanged(ratio);
}

void ScrollBar::setOrientation(int orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    emit orientationChanged(orientation);
}
