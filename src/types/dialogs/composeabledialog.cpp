#include "composeabledialog.h"
#include <QDir>
#include <QJsonArray>
#include <QDebug>
#include <QRegularExpression>
#include <QVariantMap>

QQmlEngine* ComposeableDialog::s_qmlEngine = NULL;

int ComposeableDialog::enumeratedPanelType(QQuickItem *panel) const
{
    QString componentName = this->componentType(panel);
    static const int enumIndex = this->metaObject()->indexOfEnumerator("Panels");
    static const QMetaEnum panelsEnum = this->staticMetaObject.enumerator(enumIndex);

    return panelsEnum.keysToValue(componentName.toLocal8Bit().constData());
}

const char* ComposeableDialog::panelMainProperty(QQuickItem* panel) const
{
    static const QMap<int, const char*> panelProperty {
        { ComposeableDialog::ComboBox, "currentItem" },
        { ComposeableDialog::LineEdit, "text" },
        { ComposeableDialog::Slider, "value" },
        { ComposeableDialog::CheckBox, "checked" },
        { ComposeableDialog::RadioButtons, "currentItem" }
    };

    const int panelNameEnumerated = this->enumeratedPanelType(panel);
    return panelProperty[panelNameEnumerated];
}

const char *ComposeableDialog::panelMainPropertySetter(QQuickItem *panel) const
{
    static const QMap<int, const char*> panelProperty {
        { ComposeableDialog::ComboBox, "currentItem" },
        { ComposeableDialog::LineEdit, "text" },
        { ComposeableDialog::Slider, "value" },
        { ComposeableDialog::CheckBox, "checked" },
        { ComposeableDialog::RadioButtons, "currentItemSetter" }
    };

    const int panelNameEnumerated = this->enumeratedPanelType(panel);
    return panelProperty[panelNameEnumerated];
}

QString ComposeableDialog::componentType(QQuickItem *panel) const
{
    static const QRegularExpression re("Panel_\\w+");
    return QString(panel->metaObject()->className()).remove(re);
}

QVariant ComposeableDialog::defaultPanelProperty(QQuickItem *panel) const
{
    const int componentNameEnumerated = this->enumeratedPanelType(panel);

    if(componentNameEnumerated & (ComposeableDialog::ComboBox | ComposeableDialog::RadioButtons))
        return QVariant(panel->property("model").toList()[0]);

    else if(componentNameEnumerated == ComposeableDialog::LineEdit)
        return QVariant("");

    else if(componentNameEnumerated == ComposeableDialog::Slider)
        return QVariant(panel->property("minimumValue"));

    else if(componentNameEnumerated == ComposeableDialog::CheckBox)
        return QVariant(false);

    Q_ASSERT_X(false, "Panel default property", "not defined");
}

ComposeableDialog::ComposeableDialog(QQuickItem *parent): PaintedItem(parent)
{
    m_dirPath = "";
    m_mode = "None";
    m_titleColor = QColor("lightGray");
    m_componentFactory = new DynamicComponentFactory(s_qmlEngine, this);
    m_settingsProvider = new TagSettingsProvider;

    this->setClip(true);

    connect(this, &ComposeableDialog::dirPathChanged, this, &ComposeableDialog::reloadSettings);
    connect(this, &ComposeableDialog::modeChanged, this, &QQuickItem::update);
    connect(this, &ComposeableDialog::modeChanged, this, &ComposeableDialog::showAndHide);
    connect(this, &ComposeableDialog::titleColorChanged, this, &QQuickItem::update);
    connect(m_settingsProvider, &TagSettingsProvider::updated, [this]() {
        Q_EMIT this->settingUpdated(m_settingsProvider->settings());
    });
    connect(this, &ComposeableDialog::modeChanged, [this](QString mode) {
        const QMap<QString, QString> longNames = m_settingsProvider->extractSettingsLongNames();

        if(mode == "None") {
            m_titleColor = QColor("lightGray");
        }

        if(longNames.keys().contains(mode))
            m_longName = longNames[mode];
        else
            m_longName = mode;
    });
}

void ComposeableDialog::paint(QPainter *painter)
{
    painter->setPen(m_color);
    painter->setBrush(m_color);

    painter->drawRect(0, 0, this->width(), this->height());

    const QFontMetrics fm(m_font);
    painter->setPen(QColor("lightGray"));
    painter->drawLine(20, fm.height(), this->width() - 20, fm.height());

    // draw title
    painter->setFont(m_font);
    painter->setPen(m_titleColor);
    painter->drawText(QPoint(20, m_font.pixelSize()), m_longName);
}

void ComposeableDialog::setEngine(QQmlEngine *engine)
{
    ComposeableDialog::s_qmlEngine = engine;
}

ComposeableDialogView* ComposeableDialog::newView(QString name)
{
    const double yPos = QFontMetricsF(m_font).height() + 2.;
    ComposeableDialogView* view = new ComposeableDialogView(QPointF(0, yPos), QPointF(this->width(), yPos), this);
    view->setY(yPos);
    view->setWidth(this->width());
    view->setHeight(this->height() - yPos);
    view->setColor(m_color);

    connect(this, &ComposeableDialog::widthChanged, [this, view]() { view->setWidth(this->width()); });
    connect(this, &ComposeableDialog::heightChanged, [this, view]() { view->setHeight(this->height() - (QFontMetricsF(m_font).height() + 22)); });

    m_views.insert(name, view);

    return view;
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
    QVariantMap options;

    for(QQuickItem* panel: m_components[m_mode]) {
        const QString panelName = panel->property("name").toString();

        options[panelName] = panel->property(this->panelMainProperty(panel));
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

void ComposeableDialog::showAndHide()
{
    if(!m_views.keys().contains(m_mode))
        return;

    m_views[m_mode]->hide(false);

    for(ComposeableDialogView* view: m_views.values())
        view->setZ(0);

    m_views[m_mode]->setZ(1);
    m_views[m_mode]->show();
}

void ComposeableDialog::createDialogComponents()
{
    QJsonObject componentSettings;
    QJsonValue vComponentsSettings;
    QQuickItem* component = NULL;
    ComposeableDialogView *view = NULL;
    QString componentType;
    const QStringList names = m_settingsProvider->extractSettingsNames();
    view = this->newView("None");

    // TODO validate
    for(QString dialogName: names) {
        int componentY = 0;
        vComponentsSettings = m_settingsProvider->tagOptions(dialogName);

        // ---------creating view------------------;
        view = this->newView(dialogName);

        if(dialogName != m_mode)
            view->setPosition(QPointF(this->width(), 0));
        // ----------------------------------------

        for(QJsonValue vSingleComponentSettings: vComponentsSettings.toArray()) {
            componentSettings = vSingleComponentSettings.toObject();
            componentType = componentSettings["type"].toString();

            component = m_componentFactory->create(
                QUrl(QString("qrc:/qml/components/panels/composeable/%1Panel.qml").arg(componentType)),
                SettingsProvider::extractSettings({"type"}, componentSettings),
                view
            );

            // to make dropdown visible
            if(componentType == "ComboBox")
                component->setZ(6);
            component->setY(componentY);
            component->setProperty("width", this->width());
            if(componentType != "RadioButtons")
                component->setProperty("height", m_panelHeight);
            componentY += component->height();

            // add resizing
            connect(this, &ComposeableDialog::panelHeightChanged, component, &QQuickItem::setHeight);
            connect(this, &ComposeableDialog::widthChanged, [this, component]() {
                component->setProperty("width", this->width());
            });

            m_components[dialogName].append(component);
        }
    }

    this->showAndHide();
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

void ComposeableDialog::setDialogOptions(QVariantMap options)
{
    for(QQuickItem* panel: m_components[m_mode]) {
        const QString componentName = panel->property("name").toString();
        if(options.keys().contains(componentName))
            panel->setProperty(this->panelMainPropertySetter(panel), options[componentName]);
        else
            panel->setProperty(this->panelMainPropertySetter(panel), this->defaultPanelProperty(panel));
    }
}

