#ifndef CloneManager_H
#define CloneManager_H

#include <QPointer>
#include <QVector>
#include "clonetag.h"
#include <QObject>
#include <QQuickItem>
#include "tagappearance.h"

template<typename CloneType>
class CloneManager
{
    private:
        void reindex(int removedIndex);

    protected:
        QVector<QPointer<CloneType> > m_instances;

    public:
        QPointer<CloneType> clone(TagAppearance* appearance, QQuickItem* parent);
        QVector<QPointer<CloneType> > instances() const;
};

template<typename CloneType>
void CloneManager<CloneType>::reindex(int removedIndex)
{
    for(int i = removedIndex; i < m_instances.length(); i++)
        m_instances[i]->setIndex(m_instances[i]->index() - 1);
}

template<typename CloneType>
QPointer<CloneType> CloneManager<CloneType>::clone(TagAppearance *appearance, QQuickItem *parent)
{
    int index = m_instances.length();
    QPointer<CloneType> instance = new CloneType(index, appearance, parent);
    //instance->setPosition(QPointF(parent->x(), parent->y()));
    instance->setX(10);
    instance->setY(10);
    instance->grabMouse();

    m_instances.append(instance);

    QObject::connect(instance.data(), &CloneType::deleteRequest, [this](int index) {
        m_instances[index]->deleteLater();
        m_instances.remove(index);
        this->reindex(index);
    });

    return instance;
}

template<typename CloneType>
QVector<QPointer<CloneType> > CloneManager<CloneType>::instances() const
{
    return m_instances;
}
#endif // CloneManager_H
