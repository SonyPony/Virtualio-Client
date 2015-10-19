#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QWidget>
#include <QQmlEngine>
#include <QIcon>
#include <QTimer>

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

#include "types/controls/styledbutton.h"
#include "types/controls/noninteractivescrollbar.h"

#include "tests/tests.h"
#include "tests/intervaltests.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    qmlRegisterType<StyledButton>("StyledButton", 1, 0, "StyledButton");
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

    QIcon icon(QPixmap(16, 16));
    QQuickWidget *quickWidget = new QQuickWidget;
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->resize(1000, 500);
    quickWidget->setWindowTitle("Syntrio Creator");
    quickWidget->setWindowIcon(icon);

    quickWidget->rootContext()->setContextProperty("Formater", &formater);
    quickWidget->rootContext()->setContextProperty("Core", &core);

    quickWidget->setSource(QStringLiteral("qrc:/main.qml"));

    quickWidget->showMaximized();
    //quickWidget->show();

    Tests::IntervalTests intervalTests;
    int result = Tests::runTests(&intervalTests);

    if(QApplication::arguments().contains("--test"))
        return result;
    else
        return app.exec();
}
