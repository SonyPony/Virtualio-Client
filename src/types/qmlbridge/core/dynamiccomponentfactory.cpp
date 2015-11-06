#include "dynamiccomponentfactory.h"
#include <QQmlComponent>
#include <QFileInfo>
#include <QJsonValue>

DynamicComponentFactory::DynamicComponentFactory(QQmlEngine *engine, QObject *parent) : QObject(parent)
{
    m_qmlEngine = engine;
}

QQuickItem* DynamicComponentFactory::create(QUrl url, QJsonObject settings, QQuickItem *parentItem)
{
    QFileInfo fileInfo(url.toString().replace("qrc:/", ":/"));
    if(!fileInfo.exists()) {
        Q_EMIT error("File does not exists.");
        return NULL;
    }

    QQmlComponent component(m_qmlEngine);
    component.loadUrl(url);
    // item created
    QQuickItem* item = qobject_cast<QQuickItem*>(component.create());
    // check wheter component was created successfully
    if(component.isError()) {
        Q_EMIT qmlErrors(component.errors());
        return NULL;
    }

    // need to set parent item to be painted
    item->setParentItem(parentItem);

    // set desired properties
    for(QString propertyName: settings.keys())
        item->setProperty(propertyName.toLatin1().data(), settings[propertyName].toVariant());

    return item;
}

