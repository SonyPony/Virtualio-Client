#include "cloneabletag.h"

CloneableTag::CloneableTag(ExtentedEnums::Direction direction, QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    m_manager = new CloneManager<CloneTag>;
    m_tagAppearance = new TagAppearance("", QColor("black"), QColor("white"), direction, this);
    setAcceptedMouseButtons(Qt::LeftButton);

    connect(this, SIGNAL(widthChanged()), this, SLOT(resizeAppearance()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(resizeAppearance()));
}

CloneableTag::CloneableTag(QString name, QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction, QObject *parent): QQuickPaintedItem((QQuickItem*)parent)
{
    m_manager = new CloneManager<CloneTag>;
    m_tagAppearance = new TagAppearance(name, firstColor, secondColor, direction, this);
    setAcceptedMouseButtons(Qt::LeftButton);

    connect(this, SIGNAL(widthChanged()), this, SLOT(resizeAppearance()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(resizeAppearance()));
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

