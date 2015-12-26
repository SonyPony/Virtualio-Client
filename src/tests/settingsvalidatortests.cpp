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

    QCOMPARE(v.checkRootObject(settings), QStringLiteral("Expected (moduleSettings, tagOptions) keys"));
    QCOMPARE(errorSpy.count(), 1);

    settings = objectWithName("valid");
    QCOMPARE(v.checkRootObject(settings), QStringLiteral(""));
    QCOMPARE(errorSpy.count(), 1);
}

void Tests::SettingsValidatorTests::testCheckTagStyle()
{
    SettingsValidator v;
    QJsonObject settings = objectWithName("invalidTagStyle")["tagStyle"].toObject();
    QSignalSpy errorSpy(&v, SIGNAL(error(QString)));

    QCOMPARE(v.checkTagStyle(settings), QStringLiteral("At key primaryColor expected value type string instead of double"));
    QCOMPARE(errorSpy.count(), 1);

    settings = objectWithName("valid")["tagStyle"].toObject();
    QCOMPARE(v.checkTagStyle(settings), QStringLiteral(""));
    QCOMPARE(errorSpy.count(), 1);
}

void Tests::SettingsValidatorTests::testCheckTagOptions()
{
    SettingsValidator v;
    QJsonArray settings = objectWithName("invalidComboBox")["tagOptions"].toArray();
    QSignalSpy errorSpy(&v, SIGNAL(error(QString)));

    // test invalid combobox
    QCOMPARE(v.checkTagOptions(settings), QStringLiteral("At key model expected value type array instead of double"));
    QCOMPARE(errorSpy.count(), 1);

    // test invalid tag options
    settings = objectWithName("invalidTagOptions")["tagOptions"].toArray();
    QCOMPARE(v.checkTagOptions(settings), QStringLiteral("Expected value type object instead of double"));
    QCOMPARE(errorSpy.count(), 2);

    // test valid
    settings = objectWithName("valid")["tagOptions"].toArray();
    QCOMPARE(v.checkTagOptions(settings), QStringLiteral(""));
    QCOMPARE(errorSpy.count(), 2);
}

