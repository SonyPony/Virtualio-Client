#include "modulesconnectionview.h"

ModulesConnectionView::ModulesConnectionView(QQuickItem *parent): PaintedItem(parent)
{
    m_color = QColor("transparent");
    m_modulesNames = QStringList();
    m_connectionTablePos = 0;

    connect(this, &ModulesConnectionView::modulesNamesChanged, [this]() {
        m_modulesStates.clear();

        for(const QString& name: m_modulesNames)
            m_modulesStates[name] = ModuleState::Discconnected;
    });

    connect(this, &ModulesConnectionView::modulesNamesChanged, this, &ModulesConnectionView::generatePanels);
}

void ModulesConnectionView::paint(QPainter *painter)
{
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(this->boundingRect());
}

void ModulesConnectionView::registerType()
{
    qmlRegisterType<ModulesConnectionView>("ModulesConnectionView", 1, 0, "ModulesConnectionView");
    qmlRegisterType<ModuleState>("ModuleState", 1, 0, "ModuleState");
}

QStringList ModulesConnectionView::modulesNames() const
{
    return m_modulesNames;
}

QFont ModulesConnectionView::font() const
{
    return m_font;
}

int ModulesConnectionView::connectionTablePos() const
{
    return m_connectionTablePos;
}

QColor ModulesConnectionView::inactiveColor() const
{
    return m_inactiveColor;
}

QColor ModulesConnectionView::activeColor() const
{
    return m_activeColor;
}

QColor ModulesConnectionView::nameColor() const
{
    return m_nameColor;
}

void ModulesConnectionView::generatePanels()
{
    ModuleConnectionPanel* panel = NULL;
    for(const QString& name: m_modulesNames) {
        const int index = m_modulesNames.indexOf(name);

        panel = new ModuleConnectionPanel(this);
        m_connectionPanels[name] = panel;

        panel->setParentItem(this);

        panel->setActiveColor(m_activeColor);
        panel->setInactiveColor(m_inactiveColor);
        panel->setWidth(this->width());
        panel->setHeight(this->height() / m_modulesNames.length());
        panel->setY(index * panel->height());
        panel->setModuleName(name);
        panel->setConnectionStatePos(m_connectionTablePos);
        panel->setColor(m_color);
        panel->setFont(m_font);
        panel->setNameColor(m_nameColor);

        connect(this, &ModulesConnectionView::nameColorChanged, panel, &ModuleConnectionPanel::setNameColor);
        connect(this, &ModulesConnectionView::activeColorChanged, panel, &ModuleConnectionPanel::setActiveColor);
        connect(this, &ModulesConnectionView::inactiveColorChanged, panel, &ModuleConnectionPanel::setInactiveColor);
        connect(this, &ModulesConnectionView::connectionTablePosChanged, panel, &ModuleConnectionPanel::setConnectionStatePos);
        connect(this, &ModulesConnectionView::fontChanged, panel, &ModuleConnectionPanel::setFont);
        connect(this, &ModulesConnectionView::colorChanged, panel, &ModuleConnectionPanel::setColor);

        connect(this, &ModulesConnectionView::widthChanged, [this, panel]() {
            panel->setWidth(this->width());
        });

        connect(this, &ModulesConnectionView::heightChanged, [this, panel, index]() {
            panel->setHeight(this->height() / m_modulesNames.length());
            panel->setY(index * panel->height());
        });
    }
}

void ModulesConnectionView::setModulesNames(QStringList modulesNames)
{
    if (m_modulesNames == modulesNames)
        return;

    m_modulesNames = modulesNames;
    emit modulesNamesChanged(modulesNames);
}

void ModulesConnectionView::setModuleState(QString name, int state)
{
    Q_ASSERT(m_modulesStates.keys().contains(name));
    m_modulesStates[name] = state;
    m_connectionPanels[name]->setConnectionState(state);

    this->update();
}

void ModulesConnectionView::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void ModulesConnectionView::setConnectionTablePos(int connectionTablePos)
{
    if (m_connectionTablePos == connectionTablePos)
        return;

    m_connectionTablePos = connectionTablePos;
    emit connectionTablePosChanged(connectionTablePos);
}

void ModulesConnectionView::setInactiveColor(QColor inactiveColor)
{
    if (m_inactiveColor == inactiveColor)
        return;

    m_inactiveColor = inactiveColor;
    emit inactiveColorChanged(inactiveColor);
}

void ModulesConnectionView::setActiveColor(QColor activeColor)
{
    if (m_activeColor == activeColor)
        return;

    m_activeColor = activeColor;
    emit activeColorChanged(activeColor);
}

void ModulesConnectionView::setNameColor(QColor nameColor)
{
    if (m_nameColor == nameColor)
        return;

    m_nameColor = nameColor;
    emit nameColorChanged(nameColor);
}

