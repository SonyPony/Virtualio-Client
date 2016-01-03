#include "cloneabletag.h"
#include <QPropertyAnimation>

void CloneableTag::init()
{
    m_manager = new CloneManager<CloneTag>;
    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setDuration(350);

    this->setAcceptedMouseButtons(Qt::LeftButton);

    connect(this, SIGNAL(widthChanged()), this, SLOT(resizeAppearance()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(resizeAppearance()));
    connect(this, &CloneableTag::opacityChanged, [this]() {
        this->setVisible(this->opacity() != 0.);
    });
}

CloneableTag::CloneableTag(ExtentedEnums::Direction direction, QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    this->init();

    m_tagAppearance = new TagAppearance("", QColor("black"), QColor("white"), direction, this);
}

CloneableTag::CloneableTag(QString name, QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction, QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    this->init();

    m_tagAppearance = new TagAppearance(name, firstColor, secondColor, direction, this);
}

TagAppearance *CloneableTag::appearance()
{
    return m_tagAppearance;
}

void CloneableTag::paint(QPainter *painter)
{
    m_tagAppearance->paintTag(painter);
}

void CloneableTag::mousePressEvent(QMouseEvent *)
{
    QPointer<CloneTag> instance = m_manager->clone(m_tagAppearance, this);
    instance->grabMouse();

    Q_EMIT this->newObject(instance);
    Q_EMIT instance->catched();
}

void CloneableTag::resizeAppearance()
{
    m_tagAppearance->setSize(QSizeF(width(), height()));
}

void CloneableTag::fadeIn()
{
    m_opacityAnimation->stop();
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->start();
}

void CloneableTag::fadeOut()
{
    m_opacityAnimation->stop();
    m_opacityAnimation->setEndValue(0);
    m_opacityAnimation->start();
}

