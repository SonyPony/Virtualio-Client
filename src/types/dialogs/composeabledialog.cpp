#include "composeabledialog.h"
#include <QDir>
#include <QJsonArray>
#include <QDebug>
#include <QRegularExpression>

QQmlEngine* ComposeableDialog::s_qmlEngine = NULL;

ComposeableDialog::ComposeableDialog(QQuickItem *parent): m_dirPath(""), PaintedItem(parent)
{
    m_componentFactory = new DynamicComponentFactory(s_qmlEngine, this);
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

    const QFontMetrics fm(m_font);
    painter->setPen(QColor("light gray"));
    painter->drawLine(20, fm.height(), this->width() - 20, fm.height());

    // draw title
    painter->setFont(m_font);
    painter->setPen(m_titleColor);
    painter->drawText(QPoint(20, m_font.pixelSize()), m_mode);
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

    static const int enumIndex = this->metaObject()->indexOfEnumerator("Panels");
    static const QMetaEnum panelsEnum = this->staticMetaObject.enumerator(enumIndex);
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

    return options;
}

QColor ComposeableDialog::titleColor() const
{
    return m_titleColor;
}

QFont ComposeableDialog::font() const
{
    return m_font;
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
    const double offset = (double)m_font.pixelSize() * 1.5;
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
            component->setY(m_panelHeight * m_components[dialogName].length() + offset);
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

void ComposeableDialog::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void ComposeableDialog::setTitleColor(QColor titleColor)
{
    if (m_titleColor == titleColor)
        return;

    m_titleColor = titleColor;
    emit titleColorChanged(titleColor);
}

