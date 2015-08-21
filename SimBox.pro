TEMPLATE = app
CONFIG += c++11
QT += qml quick widgets serialport

SOURCES += main.cpp \
    types/hardware/serialcommunication.cpp \
    types/hardware/measurement/formater.cpp \
    core/interval.cpp \
    core/core.cpp \
    types/controls/visualization/abstractgraphcontent.cpp \
    types/controls/visualization/graphcontent.cpp \
    types/controls/resizeableitem.cpp \
    types/controls/visualization/abstractgraphaxis.cpp \
    types/controls/visualization/graphaxis.cpp \
    types/controls/visualization/graphview.cpp \
    core/draganddropmanager.cpp \
    types/controls/noninteractivescrollbar.cpp

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
    types/controls/visualization/abstractgraphcontent.h \
    types/controls/visualization/graphcontent.h \
    types/controls/resizeableitem.h \
    types/controls/visualization/abstractgraphaxis.h \
    types/controls/visualization/graphaxis.h \
    types/controls/visualization/graphview.h \
    core/draganddropmanager.h \
    types/controls/noninteractivescrollbar.h
