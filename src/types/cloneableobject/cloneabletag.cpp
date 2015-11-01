#include "cloneabletag.h"

CloneableTag::CloneableTag()
{
    m_manager = new CloneManager<CloneTag>;
    m_tagAppearance = new TagAppearance(QColor("#E6063C"), QColor("#C40002"), ExtentedEnums::Left, this);
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, SIGNAL(widthChanged()), this, SLOT(resizeAppearance()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(resizeAppearance()));
}

void CloneableTag::paint(QPainter *painter)
{
    painter->setBrush(QBrush("blue"));
    //painter->drawRect(boundingRect());

    m_tagAppearance->paintTag(painter);
}

void CloneableTag::mousePressEvent(QMouseEvent *)
{
    QPointer<CloneTag> instance = m_manager->clone(m_tagAppearance, this);
    instance->grabMouse();
    emit newObject(instance);
}

void CloneableTag::resizeAppearance()
{
    m_tagAppearance->setSize(QSizeF(width(), height()));
}

