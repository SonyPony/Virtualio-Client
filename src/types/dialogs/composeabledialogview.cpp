#include "composeabledialogview.h"

ComposeableDialogView::ComposeableDialogView(QQuickItem *parent): PaintedItem(parent)
{
    this->setParentItem(parent);
    this->setClip(true);

    m_moveAnimation = new MoveAnimation(this, 250, this);
    m_moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
}

ComposeableDialogView::ComposeableDialogView(QPointF showPos, QPointF hidePos, QQuickItem *parent)
{
    this->setParentItem(parent);

    m_moveAnimation = new MoveAnimation(this, 250, this);
    m_moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_showPos = showPos;
    m_hidePos = hidePos;
}

void ComposeableDialogView::paint(QPainter *painter)
{
    painter->setPen(m_color);
    painter->setBrush(m_color);

    painter->drawRect(this->boundingRect());
}

void ComposeableDialogView::setShowPosition(QPointF point)
{
    m_showPos = point;
}

void ComposeableDialogView::setHidePosition(QPointF point)
{
    m_hidePos = point;
}

void ComposeableDialogView::show(bool animate)
{
    if(!animate) {
        this->setPosition(m_showPos);
        return;
    }
    m_moveAnimation->stop();
    m_moveAnimation->setStartValue(this->position());
    m_moveAnimation->setEndValue(m_showPos);
    m_moveAnimation->start();
}

void ComposeableDialogView::hide(bool animate)
{
    if(!animate) {
        this->setPosition(m_hidePos);
        return;
    }
    m_moveAnimation->stop();
    m_moveAnimation->setStartValue(this->position());
    m_moveAnimation->setEndValue(m_hidePos);
    m_moveAnimation->start();
}

