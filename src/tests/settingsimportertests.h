#ifndef SETTINGSIMPORTERTESTS_H
#define SETTINGSIMPORTERTESTS_H

#include <QObject>
#include <QDir>
#include <QTest>

namespace Tests {
    class SettingsImporterTests : public QObject
    {
            Q_OBJECT
        private:
            QDir m_dir;

        public:
            SettingsImporterTests(QDir& dir, QObject *parent = 0);

        private Q_SLOTS:
            void testLoadSettings();
    };
}

#endif // SETTINGSIMPORTERTESTS_H
