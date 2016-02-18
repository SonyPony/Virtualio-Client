#ifndef GRAPHSWIDGET_H
#define GRAPHSWIDGET_H

#include <QQuickItem>
#include <QVariantMap>

#include <types/qmlbridge/dynamiccomponentmanager.h>

class GraphsWidget : public DynamicComponentManager
{
        Q_OBJECT
    private:
        QVariantMap m_datas;
        QMap<QString, QQuickItem*> m_graphs;

    public:
        GraphsWidget(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

    private Q_SLOTS:
        void generateGraphs();

    public Q_SLOTS:
        void clearAll();
        void setGraphsDatas(QVariantMap datas);
};

#endif // GRAPHSWIDGET_H
