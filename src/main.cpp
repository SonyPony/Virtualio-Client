#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QWidget>
#include <QQmlEngine>
#include <QIcon>
#include <QObject>
#include <QDir>

#include <types/containers/tagscontainer.h>

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
#include "types/controls/maintabsselection.h"
#include "types/containers/scrollview.h"

#include "interval.h"
#include "core.h"

#include "types/controls/tagmenuselection.h"
#include "types/controls/clickabletext.h"
#include "types/controls/scrollbar.h"
#include "types/controls/styledbutton.h"
#include "types/controls/noninteractivescrollbar.h"

#include "types/dialogs/composeabledialog.h"

#include "tests/tests.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickWidget *quickWidget = new QQuickWidget;
    ComposeableDialog::setEngine(quickWidget->engine());

    qmlRegisterSingletonType(QUrl(QStringLiteral("qrc:/qml/styles/StyleSettings.qml")), "StyleSettings", 1, 0, "StyleSettings");

    qmlRegisterType<TagsContainer>("TagsContainer", 1, 0, "TagsContainer");
    qmlRegisterType<TagMenuSelection>("TagMenuSelection", 1, 0, "TagMenuSelection");
    qmlRegisterType<ComposeableDialog>("ComposeableDialog", 1, 0, "ComposeableDialog");
    qmlRegisterType<Interval>("Interval", 1, 0, "Interval");
    qmlRegisterType<SerialCommunication>("SerialCommunication", 1, 0, "SerialCommunication");

    qmlRegisterType<StyledButton>("StyledButton", 1, 0, "StyledButton");
    qmlRegisterType<NonInteractiveScrollBar>("NonInteractiveScrollBar", 1, 0, "NonInteractiveScrollBar");
    qmlRegisterType<ScrollBar>("ScrollBar", 1, 0, "ScrollBar");

    qmlRegisterType<CloneableTag>("CloneableTag", 1, 0, "CloneableTag");

    qmlRegisterType<GraphAxis>("GraphAxis", 1, 0, "GraphAxis");
    qmlRegisterType<GraphContent>("GraphContent", 1, 0, "GraphContent");
    qmlRegisterType<GraphView>("GraphView", 1, 0, "GraphView");

    qmlRegisterType<DropGrid>("DropGrid", 1, 0, "DropGrid");

    qmlRegisterType<TagableDIL>("TagableDIL", 1, 0, "TagableDIL");

    qmlRegisterType<ScrollView>("ScrollView", 1, 0, "ScrollView");
    qmlRegisterType<VerticalTabView>("VerticalTabView", 1, 0, "VerticalTabView");
    qmlRegisterType<Tab>("Tab", 1, 0, "Tab");
    qmlRegisterType<MainTabsSelection>("MainTabsSelection", 1, 0, "MainTabsSelection");
    qmlRegisterType<ClickableText>("ClickableText", 1, 0, "ClickableText");

    Formater formater;
    Core core;

    QIcon icon(QPixmap(":/resources/images/VirtualioIcon.png"));

    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->resize(1000, 500);
    quickWidget->setWindowTitle("VirtualIO Creator");
    quickWidget->setWindowIcon(icon);

    quickWidget->rootContext()->setContextProperty("Formater", &formater);
    quickWidget->rootContext()->setContextProperty("Core", &core);

    quickWidget->setSource(QStringLiteral("qrc:/main.qml"));

    quickWidget->showMaximized();
    //quickWidget->show();

    int result = Tests::run(QDir::current());

    qDebug() << "----------TESTS " << ((result) ?"FAILED" :"PASSED") << "----------";

    if(QApplication::arguments().contains("--test"))
        return result;
    else
        return app.exec();
}
