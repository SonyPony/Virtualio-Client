#include "dynamiccomponentmanager.h"

QQmlEngine* DynamicComponentManager::s_qmlEngine = NULL;
QQuickItem* DynamicComponentManager::s_rootObject = NULL;
RootObjectChangeWrapper* DynamicComponentManager::s_rootObjectChangeEmitter = new RootObjectChangeWrapper;

DynamicComponentManager::DynamicComponentManager(QQuickItem *parent): PaintedItem(parent)
{
    m_componentFactory = new DynamicComponentFactory(s_qmlEngine, this);
}

void DynamicComponentManager::setRootObject(QQuickItem *object)
{
    Q_ASSERT(object != NULL);
    DynamicComponentManager::s_rootObject = object;

    DynamicComponentManager::s_rootObjectChangeEmitter->emitRootObjectChanged(object);
}

void DynamicComponentManager::setEngine(QQmlEngine *engine)
{
    Q_ASSERT(engine != NULL);
    DynamicComponentManager::s_qmlEngine = engine;
}



void RootObjectChangeWrapper::emitRootObjectChanged(QQuickItem *object)
{
    Q_EMIT this->rootObjectChanged(object);
}
