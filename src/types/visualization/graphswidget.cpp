#include "graphswidget.h"

#include <QPainter>

GraphsWidget::GraphsWidget(QQuickItem *parent): DynamicComponentManager(parent)
{
    m_color = QColor("transparent");
}

void GraphsWidget::paint(QPainter *painter)
{
    painter->setBrush(m_color);
    painter->drawRect(this->boundingRect());
}

void GraphsWidget::generateGraphs()
{
    QJsonObject settings;
    QQuickItem* component = NULL;
    const double singleGraphHeight = this->height() / (double)m_datas.keys().length();

    for(const QString& graphLabel: m_datas.keys()) {
        Q_ASSERT(m_datas[graphLabel].canConvert(QMetaType::QVariantMap));

        const int index = m_datas.keys().indexOf(graphLabel);
        settings = QJsonObject::fromVariantMap(m_datas[graphLabel].toMap());
        settings["label"] = graphLabel;


        component = m_componentFactory->create(
            QUrl(QStringLiteral("qrc:/qml/components/visualization/ResizeableGraph.qml")),
            settings,
            this
        );

        Q_ASSERT(component != NULL);
        m_graphs[graphLabel] = component;

        component->setProperty("width", this->width());
        component->setProperty("contentHeight", singleGraphHeight * 0.7);
        component->setProperty("viewHeight", singleGraphHeight * 0.3);
        component->setProperty("y", index * singleGraphHeight);

        connect(this, &GraphsWidget::widthChanged, [this, component]() {
            component->setProperty("width", this->width());
        });
        connect(this, &GraphsWidget::heightChanged, [singleGraphHeight, component, index]() {
            component->setY(singleGraphHeight * index);
            component->setProperty("contentHeight", singleGraphHeight * 0.7);
            component->setProperty("viewHeight", singleGraphHeight * 0.3);
        });
    }
}

void GraphsWidget::clearAll()
{
    for(QQuickItem* item: m_graphs.values())
        item->deleteLater();

    m_graphs.clear();
    qDebug() << m_graphs;
}

void GraphsWidget::setGraphsDatas(QVariantMap datas)
{
    m_datas = datas;
    this->generateGraphs();
}

