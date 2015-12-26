#include "composeabledialog.h"
#include <QDir>
#include <QJsonArray>
#include <QDebug>
#include <QRegularExpression>

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

QVariantMap ComposeableDialog::dialogOptions() const
{
    const QRegularExpression re("Panel_\\w+");
    QVariantMap options;
    const int enumIndex = this->metaObject()->indexOfEnumerator("Panels");
    const QMetaEnum panelsEnum = this->staticMetaObject.enumerator(enumIndex);

    static const QMap<int, const char*> panelProperty {
        { ComposeableDialog::ComboBox, "currentItem" },
        { ComposeableDialog::LineEdit, "text" },
        { ComposeableDialog::Slider, "value" },
        { ComposeableDialog::CheckBox, "checked" },
        { ComposeableDialog::RadioButtons, "currentItem" }
    };

    for(QQuickItem* panel: m_components[m_mode]) {
        const QString componentName = QString(panel->metaObject()->className()).remove(re);
        const char* componentCharName = componentName.toLocal8Bit().constData();
        const int panelNameEnumerated = panelsEnum.keysToValue(componentCharName);
        const QString panelName = panel->property("name").toString();

        options[panelName] = panel->property(panelProperty[panelNameEnumerated]);
    }

    qDebug() << options;
    return options;
}

QString ComposeableDialog::mode() const
{
    return m_mode;
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

            //qDebug() << component << component->metaObject()->className();
            m_components[dialogName].append(component);
        }
    }
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

void ComposeableDialog::setMode(QString mode)
{
    if (m_mode == mode)
        return;

    m_mode = mode;
    emit modeChanged(mode);
}

