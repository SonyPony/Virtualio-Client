#include "dynamiccomponentmanager.h"

QQmlEngine* DynamicComponentManager::s_qmlEngine = NULL;

DynamicComponentManager::DynamicComponentManager(QQuickItem *parent): PaintedItem(parent)
{
    m_componentFactory = new DynamicComponentFactory(s_qmlEngine, this);
}

void DynamicComponentManager::setEngine(QQmlEngine *engine)
{
    Q_ASSERT(engine != NULL);
    DynamicComponentManager::s_qmlEngine = engine;
}

