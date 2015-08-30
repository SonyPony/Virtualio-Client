#include "clonetag.h"

/*CloneTag::CloneTag()
{
    setWidth(100);
    setHeight(100);
    update(QRect(0, 0, 100, 100));
}*/

CloneTag::CloneTag(int index, QObject *parent): CloneObject(index, parent)
{
    setFlag(QQuickItem::ItemAcceptsDrops);
    setAcceptedMouseButtons(Qt::AllButtons);
    setWidth(50);
    setHeight(50);
    update(boundingRect().toRect());

}

void CloneTag::paint(QPainter *painter)
{
    painter->setBrush(QBrush("red"));
    painter->drawRect(boundingRect());
}

