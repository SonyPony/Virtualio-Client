#include "composeabledialog.h"
#include <QDir>
#include <QJsonArray>
#include <QDebug>
#include <QRegularExpression>
#include <QVariantMap>
#include <QQmlContext>

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
        { ComposeableDialog::Slider, "pvalue" },
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
        { ComposeableDialog::Slider, "pvalue" },
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

QQuickItem *ComposeableDialog::createControlComponent(const QJsonObject& componentSettings, QQuickItem* parent)
{
    const QString componentType = componentSettings["type"].toString();

    QQuickItem* component = m_componentFactory->create(
        QUrl(QString("qrc:/qml/components/panels/composeable/%1Panel.qml").arg(componentType)),
        SettingsProvider::extractSettings({"type"}, componentSettings),
        parent
    );

    // to make dropdown visible
    if(componentType == "ComboBox") {
        connect(component, SIGNAL(showDropDown(QVariant)), this, SLOT(setRootAsDropDownParent(QVariant)));
        connect(component, SIGNAL(hideDropDown(QVariant)), this, SLOT(resetDropDownParent(QVariant)));
    }

    // set width and height
    component->setProperty("width", this->width());

    if(componentType != "RadioButtons") {
        component->setProperty("height", m_panelHeight);
        connect(this, &ComposeableDialog::panelHeightChanged, component, &QQuickItem::setHeight);
    }

    const QStringList interactiveComponents = {
        "Slider",
        "CheckBox",
        "LineEdit"
    };
    // bind value property
    if(interactiveComponents.contains(componentType)) {
        connect(component, SIGNAL(valueChanged(QVariant)), this, SIGNAL(controlValueChanged(QVariant)));
    }

    // lock binding
    connect(this, &ComposeableDialog::lock, [component]() {
        component->setProperty("lock", true);
    });

    connect(this, &ComposeableDialog::unlock, [component]() {
        component->setProperty("lock", false);
    });

    // add resizing
    connect(this, &ComposeableDialog::widthChanged, [this, component]() {
        component->setProperty("width", this->width());
    });

    return component;
}

ComposeableDialog::ComposeableDialog(QQuickItem *parent): DynamicComponentManager(parent)
{
    m_dirPath = "";
    m_mode = "None";
    m_longName = tr("None");
    m_titleColor = QColor("lightGray");
    m_settingsProvider = new TagSettingsProvider;
    m_heightAnimation = new QPropertyAnimation(this, "height", this);
    m_heightAnimation->setDuration(400);
    m_heightAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    this->setClip(true);
    this->setAcceptedMouseButtons(Qt::AllButtons);

    connect(this, &ComposeableDialog::dirPathChanged, this, &ComposeableDialog::reloadSettings);
    connect(this, &ComposeableDialog::modeChanged, this, &QQuickItem::update);
    connect(this, &ComposeableDialog::modeChanged, this, &ComposeableDialog::showAndHide);
    connect(this, &ComposeableDialog::modeChanged, this, &ComposeableDialog::resizeDialog);
    connect(this, &ComposeableDialog::titleColorChanged, this, &QQuickItem::update);
    connect(m_settingsProvider, &TagSettingsProvider::updated, [this]() {
        Q_EMIT this->settingUpdated(m_settingsProvider->settings());
    });

    Q_EMIT this->titleColorChanged(m_titleColor);
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

ComposeableDialogView* ComposeableDialog::newView(QString name)
{
    const double yPos = QFontMetricsF(m_font).height() + 2.;
    ComposeableDialogView* view = new ComposeableDialogView(QPointF(0, yPos), QPointF(this->width(), yPos), this);
    view->setY(yPos);
    view->setWidth(this->width());
    view->setHeight(this->height() - yPos);
    view->setColor(m_color);

    connect(this, &ComposeableDialog::widthChanged, [this, view]() { view->setWidth(this->width()); });
    connect(this, &ComposeableDialog::heightChanged, [this, view]() {
        view->setHeight(this->height() - QFontMetrics(m_font).height() - 2);
    });
    connect(view, &ComposeableDialogView::showed, this, &ComposeableDialog::hideOtherViews);

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

bool ComposeableDialog::empty() const
{
    return m_components[m_mode].empty();
}

void ComposeableDialog::setRootAsDropDownParent(QVariant vObject)
{
    QObject* obj = qvariant_cast<QObject*>(vObject);
    const QQuickItem* component = qobject_cast<QQuickItem*>(obj);

    QQuickItem* dropDown = qobject_cast<QQuickItem*>(qvariant_cast<QObject*>(component->property("_dropDown")));
    QQuickItem* comboBox = qobject_cast<QQuickItem*>(qvariant_cast<QObject*>(component->property("_comboBox")));

    QPointF absolutePos = ComposeableDialog::s_rootObject->mapFromItem(comboBox, QPointF(0, comboBox->height()));
    dropDown->setParentItem(ComposeableDialog::s_rootObject);
    dropDown->setPosition(absolutePos);
}

void ComposeableDialog::resetDropDownParent(QVariant vObject)
{
    QObject* obj = qvariant_cast<QObject*>(vObject);
    const QQuickItem* component = qobject_cast<QQuickItem*>(obj);

    QQuickItem* dropDown = qobject_cast<QQuickItem*>(qvariant_cast<QObject*>(component->property("_dropDown")));
    QQuickItem* comboBox = qobject_cast<QQuickItem*>(qvariant_cast<QObject*>(component->property("_comboBox")));

    dropDown->setParentItem(comboBox);
    dropDown->setPosition(QPointF(0, comboBox->height()));
}

void ComposeableDialog::resizeDialog()
{
    const int minHeight = QFontMetricsF(m_font).height() + 2.;
    m_heightAnimation->stop();

    m_heightAnimation->setStartValue(this->height());
    m_heightAnimation->setEndValue(minHeight + m_viewsHeight[m_mode]);

    m_heightAnimation->start();
}

void ComposeableDialog::createDialogComponentsFromSettings(QString key)
{
    QJsonArray componentsSettings;
    QQuickItem* component = NULL;
    ComposeableDialogView *view = NULL;
    const QStringList names = m_settingsProvider->extractSettingsNames();

    view = this->newView("None");
    m_viewsHeight["None"] = 0;

    // TODO validate
    for(QString dialogName: names) {
        int componentY = 0;
        componentsSettings = m_settingsProvider->extractSingleSettingsOption(dialogName, key).toArray();

        // ---------creating view------------------;
        view = this->newView(dialogName);

        if(dialogName != m_mode)
            view->setPosition(QPointF(this->width(), 0));
        // ----------------------------------------

        // -------GENERATE OPTIONS CONTROLS--------
        for(QJsonValue vSingleComponentSettings: componentsSettings) {
            const QJsonObject componentSettings = vSingleComponentSettings.toObject();
            component = this->createControlComponent(componentSettings, view);

            // set Y pos
            component->setY(componentY);
            componentY += component->height();

            m_components[dialogName].append(component);
        }
        // ----------------------------------------

        m_viewsHeight[dialogName] = componentY;
    }

    this->showAndHide();
}

void ComposeableDialog::hideOtherViews()
{
    for(ComposeableDialogView* view: m_views.values()) {
        if(view->z() < 2)
            view->setZ(0);
        else
            view->setZ(1);
    }
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

    m_views[m_mode]->setZ(2);
    m_views[m_mode]->show();
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
    const QStringList interactiveComponents = {
        "Slider",
        "CheckBox",
        "LineEdit"
    };
    QString componentType;

    for(QQuickItem* panel: m_components[m_mode]) {
        componentType = this->componentType(panel);

        if(!interactiveComponents.contains(componentType))
            continue;

        const QString componentName = panel->property("name").toString();
        disconnect(panel, SIGNAL(valueChanged(QVariant)), this, SIGNAL(controlValueChanged(QVariant)));
        if(options.keys().contains(componentName))
            panel->setProperty(this->panelMainPropertySetter(panel), options[componentName]);
        else
            panel->setProperty(this->panelMainPropertySetter(panel), this->defaultPanelProperty(panel));
        connect(panel, SIGNAL(valueChanged(QVariant)), this, SIGNAL(controlValueChanged(QVariant)));
    }
}

