#ifndef SETTINGSVALIDATORTESTS_H
#define SETTINGSVALIDATORTESTS_H

#include <QObject>
#include <QTest>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>

#include "../types/settings/settingsimporter.h"

namespace Tests {
    class SettingsValidatorTests : public QObject
    {
            Q_OBJECT
        private:
            QDir m_dir;
            SettingsImporter* m_settingsImporter;

            QJsonObject objectWithName(QString name);

        public:
            SettingsValidatorTests(QDir& dir, QObject *parent = 0);

        private Q_SLOTS:
            void testCheckRootObject();
            void testCheckTagStyle();
    };
}

#endif // SETTINGSVALIDATORTESTS_H
