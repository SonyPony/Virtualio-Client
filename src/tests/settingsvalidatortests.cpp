#include "settingsvalidatortests.h"
#include "../types/settings/settingsvalidator.h"
#include <QSignalSpy>
#include <QDebug>

QJsonObject Tests::SettingsValidatorTests::objectWithName(QString name)
{
    QJsonArray arr = m_settingsImporter->loadSettings();

    for(QJsonValue v: arr) {
        if(v.isObject()) {
            if(v.toObject()["name"] == name)
                return v.toObject();
        }
    }

    return QJsonObject();
}

Tests::SettingsValidatorTests::SettingsValidatorTests(QDir &dir, QObject *parent) : QObject(parent), m_dir(dir)
{
    m_settingsImporter = new SettingsImporter(dir, this);
}

void Tests::SettingsValidatorTests::testCheckRootObject()
{
    SettingsValidator v;
    QJsonObject settings = objectWithName("invalid");
    QSignalSpy errorSpy(&v, SIGNAL(error(QString)));

    QVERIFY(!v.checkRootObject(settings).isEmpty());
    QCOMPARE(errorSpy.count(), 1);

    settings = objectWithName("valid");
    QVERIFY(v.checkRootObject(settings).isEmpty());
    QCOMPARE(errorSpy.count(), 1);
}

void Tests::SettingsValidatorTests::testCheckTagStyle()
{
    SettingsValidator v;
    QJsonObject settings = objectWithName("invalidTagStyle")["tagStyle"].toObject();
    QSignalSpy errorSpy(&v, SIGNAL(error(QString)));

    QVERIFY(!v.checkTagStyle(settings).isEmpty());
    QCOMPARE(errorSpy.count(), 1);

    settings = objectWithName("valid")["tagStyle"].toObject();
    QVERIFY(v.checkTagStyle(settings).isEmpty());
    QCOMPARE(errorSpy.count(), 1);
}

