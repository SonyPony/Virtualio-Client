#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "types/hardware/serialcommunication.h"
#include "types/hardware/measurement/formater.h"

#include "types/controls/visualization/graphaxis.h"
#include "types/controls/visualization/graphcontent.h"


#include "core/interval.h"
#include "core/core.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    qmlRegisterType<GraphAxis>("GraphAxis", 1, 0, "GraphAxis");
    qmlRegisterType<GraphContent>("GraphContent", 1, 0, "GraphContent");

    Formater formater;
    Core core;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Formater", &formater);
    engine.rootContext()->setContextProperty("Core", &core);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
