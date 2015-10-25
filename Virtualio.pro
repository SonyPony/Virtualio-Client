TEMPLATE = subdirs

SUBDIRS += src

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32 {
    makeTestDir.commands = $(MKDIR) $$OUT_PWD/src/tests/settingsexamples
    copySettings.commands = $(COPY_DIR) $$PWD/settings $$OUT_PWD/settings
    copyTestsSettings.commands = $(COPY_DIR) $$PWD/src/tests/settingsexamples $$OUT_PWD/src/tests

    first.depends = $(first) makeTestDir copySettings copyTestsSettings
    export(first.depends)
    export(makeTestDir.commands)
    export(copySettings.commands)
    export(copyTestsSettings.commands)
    QMAKE_EXTRA_TARGETS += first makeTestDir copySettings copyTestsSettings
}
