TEMPLATE = app
CONFIG += c++11
QT += qml quick widgets serialport svg quickwidgets testlib svg

INCLUDEPATH += common

RESOURCES += qml.qrc
TARGET = ../Virtualio

win32: DESTDIR = $$OUT_PWD
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include("../deployment.pri")

QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -g -Wall -fprofile-arcs -ftest-coverage  -O0

LIBS += \
    -lgcov

HEADERS += \
    types/hardware/serialcommunication.h \
    types/hardware/measurement/formater.h \
    common/interval.h \
    common/core.h \
    types/visualization/abstractgraphcontent.h \
    types/visualization/graphcontent.h \
    common/resizeableitem.h \
    types/visualization/abstractgraphaxis.h \
    types/visualization/graphaxis.h \
    types/visualization/graphview.h \
    types/cloneableobject/cloneabletag.h \
    types/cloneableobject/cloneobject.h \
    types/cloneableobject/clonetag.h \
    types/cloneableobject/clonemanager.h \
    common/draganddropmanager.h \
    types/controls/noninteractivescrollbar.h \
    types/layout/dropgrid.h \
    types/layout/droppoint.h \
    types/layout/dropgridsectionsystem.h \
    common/dropableobject.h \
    common/painteditem.h \
    common/extentedmath.h \
    common/graphicallogic.h \
    types/layout/dropgridsmanager.h \
    types/abstracthardware/tagabledil.h \
    common/fraction.h \
    types/containers/abstracttabview.h \
    types/containers/verticaltabview.h \
    types/cloneableobject/tagappearance.h \
    types/containers/tab.h \
    types/animations/moveanimation.h \
    types/cloneableobject/tagpinview.h \
    types/controls/styledbutton.h \
    tests/tests.h \
    tests/intervaltests.h \
    tests/fractiontests.h \
    tests/settingsimportertests.h \
    types/settings/settingsimporter.h \
    types/settings/settingsprovider.h \
    tests/settingsprovidertests.h \
    types/settings/settingsvalidator.h \
    tests/settingsvalidatortests.h \
    types/controls/tabsselection.h \
    types/containers/scrollview.h \
    types/controls/scrollbar.h \
    types/visualization/graphutils.h \
    types/qmlbridge/core/dynamiccomponentfactory.h \
    types/controls/abstractbutton.h

SOURCES += main.cpp \
    types/hardware/serialcommunication.cpp \
    types/hardware/measurement/formater.cpp \
    common/interval.cpp \
    common/core.cpp \
    types/visualization/abstractgraphcontent.cpp \
    types/visualization/graphcontent.cpp \
    common/resizeableitem.cpp \
    types/visualization/abstractgraphaxis.cpp \
    types/visualization/graphaxis.cpp \
    types/visualization/graphview.cpp \
    types/cloneableobject/cloneabletag.cpp \
    types/cloneableobject/cloneobject.cpp \
    types/cloneableobject/clonetag.cpp \
    common/draganddropmanager.cpp \
    types/controls/noninteractivescrollbar.cpp \
    types/layout/dropgrid.cpp \
    types/layout/droppoint.cpp \
    types/layout/dropgridsectionsystem.cpp \
    common/dropableobject.cpp \
    common/painteditem.cpp \
    common/extentedmath.cpp \
    common/graphicallogic.cpp \
    types/layout/dropgridsmanager.cpp \
    types/abstracthardware/tagabledil.cpp \
    common/fraction.cpp \
    types/containers/abstracttabview.cpp \
    types/containers/verticaltabview.cpp \
    types/cloneableobject/tagappearance.cpp \
    types/containers/tab.cpp \
    types/animations/moveanimation.cpp \
    types/cloneableobject/tagpinview.cpp \
    #types/cloneableobject/clonemanager.tcc \
    types/controls/styledbutton.cpp \
    tests/intervaltests.cpp \
    tests/fractiontests.cpp \
    tests/settingsimportertests.cpp \
    types/settings/settingsimporter.cpp \
    types/settings/settingsprovider.cpp \
    tests/settingsprovidertests.cpp \
    types/settings/settingsvalidator.cpp \
    tests/settingsvalidatortests.cpp \
    types/controls/tabsselection.cpp \
    types/containers/scrollview.cpp \
    types/controls/scrollbar.cpp \
    types/visualization/graphutils.cpp \
    types/qmlbridge/core/dynamiccomponentfactory.cpp \
    types/controls/abstractbutton.cpp
