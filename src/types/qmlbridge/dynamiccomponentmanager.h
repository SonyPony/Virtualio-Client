#ifndef DYNAMICCOMPONENTMANAGER_H
#define DYNAMICCOMPONENTMANAGER_H

#include <QQuickItem>
#include <painteditem.h>

#include <types/qmlbridge/core/dynamiccomponentfactory.h>

class DynamicComponentManager: public PaintedItem
{
        Q_OBJECT
    protected:
        DynamicComponentFactory* m_componentFactory;
        static QQmlEngine* s_qmlEngine;

    public:
        DynamicComponentManager(QQuickItem* parent = 0);

        static void setEngine(QQmlEngine* engine);
};

#endif // DYNAMICCOMPONENTMANAGER_H
