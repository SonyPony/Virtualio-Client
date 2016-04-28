#include "projectactions.h"
#include <types/settings/filessuffix.h>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>

ProjectActions::ProjectActions(QObject *parent) : QObject(parent)
{

}

QString ProjectActions::projectName() const
{
    return m_projectName;
}

void ProjectActions::loadProjectFile(QUrl fileUrl)
{   
    // TODO load from project file
    this->setProjectName(fileUrl.fileName().split(".")[0]);

    QString folder = fileUrl.adjusted(QUrl::RemoveFilename).toString();
    folder.remove(folder.length() - 1, 1);
    if(!folder.contains("file:///"))
        folder.prepend("file:///");
    this->setProjectFolder(folder);

    qInfo() << "Loading project" << m_folder << fileUrl.adjusted(QUrl::RemoveFilename).toString() << m_projectName;

    this->loadProject();
}

void ProjectActions::loadProject()
{
    const QString folder = m_folder.toLocalFile();
    QFile projectFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::ProFileSuffix));
    QFile layoutFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::LayoutFileSuffix));
    QFile codeFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::ScriptFileSuffix));

    // loading layout
    if(layoutFile.open(QIODevice::ReadOnly))
        Q_EMIT this->layoutDataLoaded(QJsonDocument::fromJson(layoutFile.readAll()).array());

    else
        qWarning() << "Unable to load layout.";

    // loading code
    if(codeFile.open(QIODevice::ReadOnly))
        Q_EMIT this->scriptLoaded(codeFile.readAll());

    else
        qWarning() << "Unable to load code.";
}

void ProjectActions::setProjectFolder(QUrl folder)
{
    m_folder = folder;
}

void ProjectActions::newProject()
{
    const QString proFileName = QString("%1.%2")
            .arg(m_projectName)
            .arg(FilesSuffix::ProFileSuffix);
}

void ProjectActions::saveProject(QJsonArray tags, QString code)
{
    const QString folder = m_folder.toLocalFile();

    if(m_projectName == "" || folder == "") {
        Q_EMIT this->createNewProject();
        return;
    }

    QFile projectFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::ProFileSuffix));
    QFile layoutFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::LayoutFileSuffix));
    QFile codeFile(QString("%1/%2.%3").arg(folder).arg(m_projectName).arg(FilesSuffix::ScriptFileSuffix));

    // save project file
    if(projectFile.open(QIODevice::WriteOnly)) {
        projectFile.close();

        qInfo() << "Layout saved in file" << m_folder.toLocalFile() << projectFile.fileName();
    }

    else
        qWarning() << "Cannot save project.";

    // save layout file
    if(layoutFile.open(QIODevice::WriteOnly)) {
        layoutFile.write(QJsonDocument(tags).toJson());
        layoutFile.close();

        qInfo() << "Layout saved in file" << m_folder.toLocalFile() << layoutFile.fileName();
    }

    else
        qWarning() << "Cannot save layout.";

    // save code file
    if(codeFile.open(QIODevice::WriteOnly)) {
        codeFile.write(code.toUtf8());
        codeFile.close();

        qInfo() << "Code saved in file" << m_folder.toLocalFile() << codeFile.fileName();
    }

    else
        qWarning() << "Cannot save code.";
}

void ProjectActions::setProjectName(QString projectName)
{
    if (m_projectName == projectName)
        return;

    m_projectName = projectName;
    Q_EMIT projectNameChanged(projectName);
}

