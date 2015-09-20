#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QWidget>
#include <QQmlEngine>

#include "types/hardware/serialcommunication.h"
#include "types/hardware/measurement/formater.h"

#include "types/visualization/graphaxis.h"
#include "types/visualization/graphcontent.h"
#include "types/visualization/graphview.h"

#include "types/cloneableobject/clonemanager.h"
#include "types/cloneableobject/cloneabletag.h"
#include "types/cloneableobject/clonetag.h"

#include "types/layout/dropgrid.h"

#include "types/abstracthardware/tagabledil.h"

#include "types/containers/verticaltabview.h"
#include "types/containers/tab.h"

#include "interval.h"
#include "core.h"

#include "types/controls/noninteractivescrollbar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    qmlRegisterType<NonInteractiveScrollBar>("NonInteractiveScrollBar", 1, 0, "NonInteractiveScrollBar");

    qmlRegisterType<CloneableTag>("CloneableTag", 1, 0, "CloneableTag");

    qmlRegisterType<GraphAxis>("GraphAxis", 1, 0, "GraphAxis");
    qmlRegisterType<GraphContent>("GraphContent", 1, 0, "GraphContent");
    qmlRegisterType<GraphView>("GraphView", 1, 0, "GraphView");

    qmlRegisterType<DropGrid>("DropGrid", 1, 0, "DropGrid");

    qmlRegisterType<TagableDIL>("TagableDIL", 1, 0, "TagableDIL");

    qmlRegisterType<VerticalTabView>("VerticalTabView", 1, 0, "VerticalTabView");
    qmlRegisterType<Tab>("Tab", 1, 0, "Tab");

    Formater formater;
    Core core;

    QQuickWidget *quickWidget = new QQuickWidget;
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->resize(1000, 200);

    quickWidget->setSource(QStringLiteral("qrc:/main.qml"));
    quickWidget->rootContext()->setContextProperty("Formater", &formater);
    quickWidget->rootContext()->setContextProperty("Core", &core);

    quickWidget->show();

    return app.exec();
}
