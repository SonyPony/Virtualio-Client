//#include "clonemanager.h"

/*template<typename CloneType>
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
    instance->grabMouse();

    m_instances.append(instance);

    QObject::connect(instance.data(), &CloneType::deleteRequest, [this](int index) {
        m_instances[index]->deleteLater();
        m_instances.remove(index);
        reindex(index);
    });
    //connect(instance.data(), SIGNAL(deleteRequest(int)), this, SLOT(remove(int)));

    return instance;
}

template<typename CloneType>
QVector<QPointer<CloneType> > CloneManager<CloneType>::instances() const
{
    return m_instances;
}*/
