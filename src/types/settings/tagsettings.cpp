#include "tagsettings.h"

TagSettings::TagSettings(QJsonObject tagSettings, QObject *parent) : QObject(parent)
{
    m_name = tagSettings["name"].toString();
    m_tagStyle = tagSettings["tagStyle"].toObject();
    m_tagOptions = tagSettings["tagOptions"].toArray();
    m_moduleSettings = tagSettings["moduleSettings"].toObject();
}

TagSettings::TagSettings(const TagSettings &other, QObject *parent):
    m_name(other.name()),
    m_tagStyle(other.tagStyle()),
    m_tagOptions(other.tagOptions()),
    m_moduleSettings(other.moduleSettings()),
    QObject(parent)
{}

QString TagSettings::name() const
{
    return m_name;
}

QJsonObject TagSettings::tagStyle() const
{
    return m_tagStyle;
}

QJsonArray TagSettings::tagOptions() const
{
    return m_tagOptions;
}

QJsonObject TagSettings::moduleSettings() const
{
    return m_moduleSettings;
}

