#ifndef PROJECTACTIONS_H
#define PROJECTACTIONS_H

#include <QObject>
#include <QJsonArray>
#include <QUrl>

class ProjectActions : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)

    protected:
        QUrl m_folder;
        QString m_projectName;

    public:
        ProjectActions(QObject *parent = 0);

        QString projectName() const;

    private Q_SLOTS:
        void loadProject();

    public Q_SLOTS:
        void loadProjectFile(QUrl fileUrl);
        void setProjectFolder(QUrl folder);
        void newProject();
        void saveProject(QJsonArray tags, QString code);
        void setProjectName(QString projectName);

    Q_SIGNALS:
        void projectNameChanged(QString projectName);
        void layoutDataLoaded(QJsonArray data);
        void scriptLoaded(QString code);
        void createNewProject();
};

#endif // PROJECTACTIONS_H
