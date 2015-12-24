#include "composeabledialog.h"
#include <QDir>
#include <QJsonArray>
#include <QDebug>

QQmlEngine* ComposeableDialog::s_qmlEngine = NULL;

ComposeableDialog::ComposeableDialog(QQuickItem *parent): m_dirPath(""), PaintedItem(parent)
{
    m_componentFactory = new DynamicComponentFactory(s_qmlEngine, this);
    //m_settingsImporter = new SettingsImporter;
    m_settingsProvider = new TagSettingsProvider;

    connect(this, &ComposeableDialog::dirPathChanged, this, &ComposeableDialog::reloadSettings);
    connect(m_settingsProvider, &TagSettingsProvider::updated, [this]() {
        Q_EMIT this->settingUpdated(m_settingsProvider->settings());
    });
}

void ComposeableDialog::paint(QPainter *painter)
{
    painter->setPen(m_color);
    painter->setBrush(m_color);

    painter->drawRect(0, 0, this->width(), this->height());
}

void ComposeableDialog::setEngine(QQmlEngine *engine)
{
    ComposeableDialog::s_qmlEngine = engine;
}

QString ComposeableDialog::dirPath() const
{
    return m_dirPath;
}

double ComposeableDialog::panelHeight() const
{
    return m_panelHeight;
}

void ComposeableDialog::reloadSettings(QString dirPath)
{
    // changing dir will update settings as well
    m_settingsProvider->setDir(QDir::currentPath() + "/" + dirPath);
}

void ComposeableDialog::createDialogComponents()
{
    QJsonObject componentSettings;
    QJsonValue vComponentsSettings;
    QQuickItem* component = NULL;
    QString componentType;

    // TODO validate
    for(QString dialogName: m_settingsProvider->extractSettingsNames()) {
        vComponentsSettings = m_settingsProvider->tagOptions(dialogName);

        for(QJsonValue vSingleComponentSettings: vComponentsSettings.toArray()) {
            componentSettings = vSingleComponentSettings.toObject();
            componentType = componentSettings["type"].toString();

            component = m_componentFactory->create(
                        QUrl(QString("qrc:/qml/components/panels/composeable/%1Panel.qml").arg(componentType)),
                        SettingsProvider::extractSettings({"type"}, componentSettings),
                        this
            );

            // to make dropdown visible
            if(componentType == "ComboBox")
                component->setZ(6);
            component->setY(35. * m_components[dialogName].length());
            component->setProperty("width", this->width());
            component->setProperty("height", m_panelHeight);

            // add resizing
            connect(this, &ComposeableDialog::panelHeightChanged, component, &QQuickItem::setHeight);
            connect(this, &ComposeableDialog::widthChanged, [this, component]() {
                component->setProperty("width", this->width());
            });

            m_components[dialogName].append(component);
        }
    }
    /*for(QJsonValue vSingleDialogSettings: settings) {
        singleDialogSettings = vSingleDialogSettings.toObject();

        for(QJsonValue vComponentSettings: singleDialogSettings["tapOptions"].toArray()) {
            componentSettings = vComponentSettings.toObject();
            extractedComponentSettings = componentSettings;
            // remove id properties
            extractedComponentSettings.remove("name");
            extractedComponentSettings.remove("type");

            m_components[singleDialogSettings["name"].toString()].append(m_componentFactory->create(
                    QUrl(QString("qrc/components/panels/composeable/%1.qml").arg(componentSettings["type"].toString())),
                    extractedComponentSettings,
                    this
            ));
        }
    }*/

}

void ComposeableDialog::setDirPath(QString dirPath)
{
    if (m_dirPath == dirPath)
        return;

    m_dirPath = dirPath;
    emit dirPathChanged(dirPath);
}

void ComposeableDialog::setPanelHeight(double panelHeight)
{
    if (m_panelHeight == panelHeight)
        return;

    m_panelHeight = panelHeight;
    emit panelHeightChanged(panelHeight);
}

