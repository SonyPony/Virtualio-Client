#include "scrollbar.h"
#include <QSize>
#include <QPoint>
#include "interval.h"
#include "extentedmath.h"

void ScrollBar::mousePressEvent(QMouseEvent *e)
{
    m_pressedPoint = e->pos();

    // need event pos to be related to m_nonInteractiveScrollbar
    QPoint diffPoint = e->pos() - m_nonInteractiveScrollBar->pos();

    m_dragAndDropManager->pressed(diffPoint);
}

void ScrollBar::mouseMoveEvent(QMouseEvent *e)
{
    // need event pos to be related to m_nonInteractiveScrollbar
    QPoint diffPoint = e->pos() - m_nonInteractiveScrollBar->pos();

    m_dragAndDropManager->move(diffPoint);
}

void ScrollBar::mouseReleaseEvent(QMouseEvent *e)
{
    const int tolerance = 3;
    const QRect scrollBarRect = m_nonInteractiveScrollBar->rect();
    // if clicked set position
    if(ExtentedMath::distance(m_pressedPoint, QPointF(e->pos())) <= tolerance && !scrollBarRect.contains(e->pos())) {
        // need event pos to be related to m_nonInteractiveScrollbar
        QPoint diffPoint(scrollBarRect.width(), scrollBarRect.height());
        if(e->pos().y() < m_nonInteractiveScrollBar->position() && m_orientation == Qt::Vertical)
            diffPoint.ry() =  -scrollBarRect.height();
        else if(e->pos().x() < m_nonInteractiveScrollBar->position() && m_orientation == Qt::Horizontal)
            diffPoint.rx() = - scrollBarRect.width();

        // set relative pos
        m_dragAndDropManager->pressed(QPoint());
        m_dragAndDropManager->move(diffPoint);
    }

    m_dragAndDropManager->released();
}

ScrollBar::ScrollBar(QQuickItem *parent): PaintedItem(parent), m_ratio(1)
{
    m_orientation = Qt::Horizontal;
    m_nonInteractiveScrollBar = new NonInteractiveScrollBar(this);
    m_nonInteractiveScrollBar->setOrientation(m_orientation);
    m_dragAndDropManager = new DragAndDropManager(m_nonInteractiveScrollBar, this);
    m_dragAndDropManager->setEnabledOrientations(m_orientation);

    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &ScrollBar::ratioChanged, this, &ScrollBar::updateSizes);
    connect(this, &QQuickItem::widthChanged, this, &ScrollBar::updateSizes);
    connect(this, &QQuickItem::heightChanged, this, &ScrollBar::updateSizes);

    connect(this, &ScrollBar::orientationChanged, [this](int orientation) {
        this->m_dragAndDropManager->setEnabledOrientations(orientation);
        this->m_nonInteractiveScrollBar->setOrientation(orientation);
        this->updateMoveArea();
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

QPoint ScrollBar::hadleClick(QPoint clickPoint)
{
    Interval moveInterval(0, 0);

    if(m_orientation == Qt::Horizontal) {
        moveInterval.setMax(width() - m_nonInteractiveScrollBar->width());

    }

    else {
        moveInterval.setMax(height() - m_nonInteractiveScrollBar->height());
    }

    if(m_nonInteractiveScrollBar->position() > clickPoint.y()) {
        //m_nonInteractiveScrollBar->setY();
    }
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

void ScrollBar::updateMoveArea()
{
    if(m_orientation == Qt::Horizontal)
        m_dragAndDropManager->setMoveArea(QRectF(0, 0, width() - m_nonInteractiveScrollBar->width(), height()));
    else
        m_dragAndDropManager->setMoveArea(QRectF(0, 0, width(), height() - m_nonInteractiveScrollBar->height()));
}

void ScrollBar::updateSizes()
{
    updateScrollBarSize();
    updateMoveArea();
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
    Q_ASSERT(ratio > 0);

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
