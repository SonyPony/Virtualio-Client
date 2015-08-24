TEMPLATE = app
CONFIG += c++11
QT += qml quick widgets serialport

SOURCES += main.cpp \
    types/hardware/serialcommunication.cpp \
    types/hardware/measurement/formater.cpp \
    core/interval.cpp \
    core/core.cpp \
    types/visualization/abstractgraphcontent.cpp \
    types/visualization/graphcontent.cpp \
    core/resizeableitem.cpp \
    types/visualization/abstractgraphaxis.cpp \
    types/visualization/graphaxis.cpp \
    types/visualization/graphview.cpp \
    types/cloneableobject/cloneabletag.cpp \
    types/cloneableobject/cloneobject.cpp \
    types/cloneableobject/clonetag.cpp \
    types/cloneableobject/clonemanager.cpp \
    core/draganddropmanager.cpp \
    types/controls/noninteractivescrollbar.cpp
    core/dropableobject.cpp \
    core/painteditem.cpp \
    core/extentedmath.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    types/hardware/serialcommunication.h \
    types/hardware/measurement/formater.h \
    core/interval.h \
    core/core.h \
    types/visualization/abstractgraphcontent.h \
    types/visualization/graphcontent.h \
    core/resizeableitem.h \
    types/visualization/abstractgraphaxis.h \
    types/visualization/graphaxis.h \
    types/visualization/graphview.h \
    types/cloneableobject/cloneabletag.h \
    types/cloneableobject/cloneobject.h \
    types/cloneableobject/clonetag.h \
    types/cloneableobject/clonemanager.h \
    core/draganddropmanager.h \
    types/controls/noninteractivescrollbar.h
    core/dropableobject.h \
    core/painteditem.h \
    core/extentedmath.h
