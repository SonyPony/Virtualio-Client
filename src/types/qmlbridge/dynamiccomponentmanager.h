#ifndef DYNAMICCOMPONENTMANAGER_H
#define DYNAMICCOMPONENTMANAGER_H

#include <QQuickItem>
#include <painteditem.h>

#include <types/qmlbridge/core/dynamiccomponentfactory.h>

class RootObjectChangeWrapper: public QObject
{
        Q_OBJECT
    public Q_SLOTS:
        void emitRootObjectChanged(QQuickItem* object);

    Q_SIGNALS:
        void rootObjectChanged(QQuickItem* object);
};

class DynamicComponentManager: public PaintedItem
{
        Q_OBJECT
    protected:
        DynamicComponentFactory* m_componentFactory;
        static QQuickItem* s_rootObject;
        static QQmlEngine* s_qmlEngine;
        static RootObjectChangeWrapper* s_rootObjectChangeEmitter;

    public:
        DynamicComponentManager(QQuickItem* parent = 0);

        static void setRootObject(QQuickItem* object);
        static void setEngine(QQmlEngine* engine);
};

#endif // DYNAMICCOMPONENTMANAGER_H
