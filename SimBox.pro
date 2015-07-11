TEMPLATE = app

QT += qml quick widgets serialport

SOURCES += main.cpp \
    types/hardware/serialcommunication.cpp \
    types/hardware/measurement/formater.cpp \
    types/controls/visualization/abstractgraph.cpp \
    core/interval.cpp \
    types/controls/resizeableitem.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    types/hardware/serialcommunication.h \
    types/hardware/measurement/formater.h \
    types/controls/visualization/abstractgraph.h \
    core/interval.h \
    types/controls/resizeableitem.h
