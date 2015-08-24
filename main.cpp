#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "types/hardware/serialcommunication.h"
#include "types/hardware/measurement/formater.h"

#include "types/visualization/graphaxis.h"
#include "types/visualization/graphcontent.h"
#include "types/visualization/graphview.h"

#include "types/cloneableobject/clonemanager.h"
#include "types/cloneableobject/cloneabletag.h"
#include "types/cloneableobject/clonetag.h"

#include "types/layout/dropgrid.h"

#include "core/interval.h"
#include "core/core.h"

#include "types/controls/noninteractivescrollbar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    qmlRegisterType<NonInteractiveScrollBar>("NonInteractiveScrollBar", 1, 0, "NonInteractiveScrollBar");

    qmlRegisterType<CloneableTag>("CloneableTag", 1, 0, "CloneableTag");
    qmlRegisterType<CloneTag>("CloneTag", 1, 0, "CloneTag");

    qmlRegisterType<GraphAxis>("GraphAxis", 1, 0, "GraphAxis");
    qmlRegisterType<GraphContent>("GraphContent", 1, 0, "GraphContent");
    qmlRegisterType<GraphView>("GraphView", 1, 0, "GraphView");

    qmlRegisterType<DropGrid>("DropGrid", 1, 0, "DropGrid");

    Formater formater;
    Core core;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Formater", &formater);
    engine.rootContext()->setContextProperty("Core", &core);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
