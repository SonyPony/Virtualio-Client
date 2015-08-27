#include "clonemanager.h"

void CloneManager::reindex(int removedIndex)
{
    for(int i = removedIndex; i < m_instances.length(); i++)
        m_instances[i]->setIndex(m_instances[i]->index() - 1);
}

CloneManager::CloneManager()
{

}

QPointer<CloneTag> CloneManager::clone(QQuickItem *parent)
{
    int index = m_instances.length();
    QPointer<CloneTag> instance = new CloneTag(index, parent);
    m_instances.append(instance);

    connect(instance.data(), SIGNAL(deleteRequest(int)), this, SLOT(remove(int)));

    return instance;
}

void CloneManager::remove(int index)
{
    delete m_instances[index];
    m_instances.remove(index);
    reindex(index);
}

QVector<QPointer<CloneTag> > CloneManager::instances() const
{
    return m_instances;
}
