#ifndef DYNAMICCOMPONENTFACTORY_H
#define DYNAMICCOMPONENTFACTORY_H

#include <QObject>
#include <QQuickItem>
#include <QUrl>
#include <QJsonObject>
#include <QQmlEngine>

class DynamicComponentFactory : public QObject
{
        Q_OBJECT
    protected:
        QQmlEngine* m_qmlEngine;

    public:
        DynamicComponentFactory(QQmlEngine* engine, QObject *parent = 0);

    public Q_SLOTS:
        QQuickItem* create(QUrl url, QJsonObject settings, QQuickItem* parentItem);

    Q_SIGNALS:
        void componentCompleted(QQuickItem* item);
        void qmlErrors(QList<QQmlError> errors);
        void error(QString msg);
};

#endif // DYNAMICCOMPONENTFACTORY_H
