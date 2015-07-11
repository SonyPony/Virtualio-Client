#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "types/hardware/serialcommunication.h"
#include "types/hardware/measurement/formater.h"

#include "core/interval.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    Formater formater;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Formater", &formater);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
