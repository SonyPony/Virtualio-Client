#include "modaldialog.h"

ModalDialog::ModalDialog(QQuickItem *parent): PaintedItem(parent)
{
    m_backgroundOpacity = 0.8;
    m_dialogBaseSize = QSize(this->width(), 100);
    m_container = new QQuickItem(this);
    m_container->setParentItem(this);
    m_container->setSize(m_dialogBaseSize);

    m_baseOpacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_baseOpacityAnimation->setDuration(350);

    this->setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &ModalDialog::dialogBaseSizeChanged, this, &QQuickItem::update);
    connect(this, &ModalDialog::dialogBaseSizeChanged, m_container, &QQuickItem::setSize);
    connect(m_container, &QQuickItem::widthChanged, this, &ModalDialog::centerContainer);
    connect(m_container, &QQuickItem::heightChanged, this, &ModalDialog::centerContainer);
    connect(this, &ModalDialog::childrenChanged, this, &ModalDialog::registerChildren);
    connect(this, &ModalDialog::widthChanged, this, &ModalDialog::centerContainer);
    connect(this, &ModalDialog::heightChanged, this, &ModalDialog::centerContainer);
    connect(this, &ModalDialog::dialogBaseSizeChanged, this, &ModalDialog::centerContainer);
    connect(this, &ModalDialog::opacityChanged, [this]() {
        if(this->opacity() == 0.)
            this->setVisible(false);
        else
            this->setVisible(true);
    });
    connect(m_baseOpacityAnimation, &QPropertyAnimation::finished, [this] {
        if(this->opacity() == 1.)
            Q_EMIT this->showed();
        else
            Q_EMIT this->hided();
    });
}

void ModalDialog::paint(QPainter *painter)
{
    painter->setOpacity(m_backgroundOpacity);
    painter->setPen(m_backgroundColor);
    painter->setBrush(m_backgroundColor);
    painter->drawRect(this->boundingRect());

    const QPoint baseCenterPos(
        (this->width() - m_dialogBaseSize.width()) / 2.,
        (this->height() - m_dialogBaseSize.height()) / 2.
    );

    painter->setOpacity(1);
    painter->setPen(m_color);
    painter->setBrush(m_color);
    painter->drawRect(QRect(baseCenterPos, m_dialogBaseSize));
}

QSize ModalDialog::dialogBaseSize() const
{
    return m_dialogBaseSize;
}

QColor ModalDialog::backgroundColor() const
{
    return m_backgroundColor;
}

double ModalDialog::backgroundOpacity() const
{
    return m_backgroundOpacity;
}

QQuickItem *ModalDialog::container() const
{
    return m_container;
}

void ModalDialog::registerChildren()
{
    for(QQuickItem* children: this->childItems()) {
        children->setParentItem(m_container);
    }
}

void ModalDialog::centerContainer()
{
    const QPointF center(
        (this->width() - m_container->width()) / 2.,
        (this->height() - m_container->height()) / 2.
    );

    m_container->setPosition(center);
}

void ModalDialog::setDialogBaseSize(QSize dialogBaseSize)
{
    if (m_dialogBaseSize == dialogBaseSize)
        return;

    m_dialogBaseSize = dialogBaseSize;
    emit dialogBaseSizeChanged(dialogBaseSize);
}

void ModalDialog::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(backgroundColor);
}

void ModalDialog::setBackgroundOpacity(double backgroundOpacity)
{
    if (m_backgroundOpacity == backgroundOpacity)
        return;

    m_backgroundOpacity = backgroundOpacity;
    emit backgroundOpacityChanged(backgroundOpacity);
}

void ModalDialog::hide()
{
    if(this->opacity() == 0.)
        return;

    m_baseOpacityAnimation->stop();
    m_baseOpacityAnimation->setStartValue(this->opacity());
    m_baseOpacityAnimation->setEndValue(0);
    m_baseOpacityAnimation->start();
}

void ModalDialog::show()
{
    if(this->opacity() == 1.)
        return;

    m_baseOpacityAnimation->stop();
    m_baseOpacityAnimation->setStartValue(this->opacity());
    m_baseOpacityAnimation->setEndValue(1);
    m_baseOpacityAnimation->start();
}

