TEMPLATE = app

QT += qml quick widgets serialport

SOURCES += main.cpp \
    types/hardware/serialcommunication.cpp \
    types/hardware/measurement/formater.cpp \
    core/interval.cpp \
    core/core.cpp \
    types/controls/visualization/abstractgraphgrid.cpp \
    types/controls/visualization/abstractgraphcontent.cpp \
    types/controls/visualization/graphcontent.cpp \
    types/controls/visualization/graphgrid.cpp \
    types/controls/resizeableitem.cpp
    types/controls/resizeableitem.cpp \

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
    types/controls/visualization/abstractgraphgrid.h \
    types/controls/visualization/abstractgraphcontent.h \
    types/controls/visualization/graphcontent.h \
    types/controls/visualization/graphgrid.h \
    types/controls/resizeableitem.h
    types/controls/resizeableitem.h \
