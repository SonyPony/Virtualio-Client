TEMPLATE = subdirs

SUBDIRS += src

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32 {
    copydata.commands = $(COPY_DIR) $$PWD/settings $$OUT_PWD/settings
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}
