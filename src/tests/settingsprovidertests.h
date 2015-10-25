#ifndef SETTINGSPROVIDERTESTS_H
#define SETTINGSPROVIDERTESTS_H

#include <QObject>
#include <QDir>

namespace Tests {
    class SettingsProviderTests : public QObject
    {
            Q_OBJECT
        private:
            QDir m_dir;

        public:
            SettingsProviderTests(QDir& dir, QObject *parent = 0);

        private Q_SLOTS:
    };
}

#endif // SETTINGSPROVIDERTESTS_H
