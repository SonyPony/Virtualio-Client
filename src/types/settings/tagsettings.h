#ifndef TAGSETTINGS_H
#define TAGSETTINGS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>

class TagSettings final: public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString name READ name)
        Q_PROPERTY(QJsonObject tagStyle READ tagStyle)
        Q_PROPERTY(QJsonArray tagOptions READ tagOptions)
        Q_PROPERTY(QJsonObject moduleSettings READ moduleSettings)

    private:
        QString m_name;
        QJsonObject m_tagStyle;
        QJsonArray m_tagOptions;
        QJsonObject m_moduleSettings;

    public:
        TagSettings(QJsonObject tagSettings, QObject *parent = 0);
        TagSettings(const TagSettings& other, QObject *parent = 0);

        QString name() const;
        QJsonObject tagStyle() const;
        QJsonArray tagOptions() const;
        QJsonObject moduleSettings() const;
};

#endif // TAGSETTINGS_H
