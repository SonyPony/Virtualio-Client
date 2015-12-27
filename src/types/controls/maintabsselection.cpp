#include "maintabsselection.h"
#include <QImage>
#include <QPoint>
#include <QSvgRenderer>
#include <QFontMetrics>

#define QSIGNAL(className, function, params) \
    static_cast<void(className::*)params>(&className::function)

void MainTabsSelection::initSelectionItems()
{
    if(m_iconsPaths.length() != m_tabLabels.length())
        return;

    // clear
    for(MainTabSelectionItem* item: m_selectionItems) {
        m_selectionItems.removeAll(item);
        item->deleteLater();
    }

    for(const QString iconPath: m_iconsPaths) {
        const int key = m_iconsPaths.indexOf(iconPath);
        MainTabSelectionItem* selectionItem = new MainTabSelectionItem(m_tabLabels[key], iconPath, m_iconSize, this);
        connect(selectionItem, SIGNAL(selected()), m_signalMapper, SLOT(map()));

        m_signalMapper->setMapping(selectionItem, key);

        selectionItem->setParentItem(this);
        selectionItem->setColor(QColor("transparent"));
        selectionItem->setTextColor(m_textColor);
        selectionItem->setFont(m_font);

        selectionItem->setWidth(this->width());
        selectionItem->setHeight(this->width());
        selectionItem->setY(key * selectionItem->height() + key * m_spacing + 15);

        connect(this, &MainTabsSelection::textColorChanged, selectionItem, &MainTabSelectionItem::setTextColor);
        connect(this, &MainTabsSelection::fontChanged, selectionItem, &MainTabSelectionItem::setFont);
        connect(this, &MainTabsSelection::widthChanged, [this, selectionItem]() {
            selectionItem->setWidth(this->width());
            selectionItem->setHeight(this->width());
        });
    }
}

MainTabsSelection::MainTabsSelection(QObject *parent): TabSelection(parent)
{
    m_signalMapper = new QSignalMapper(this);
    setAcceptedMouseButtons(Qt::AllButtons);

    connect(m_signalMapper, QSIGNAL(QSignalMapper, mapped, (int)), this, &MainTabsSelection::tabSelected);
    connect(this, SIGNAL(iconsPathsChanged(QStringList)), this, SLOT(initSelectionItems()));
    connect(this, SIGNAL(tabLabelsChanged(QStringList)), this, SLOT(initSelectionItems()));
}

void MainTabsSelection::paint(QPainter *painter)
{
    painter->setPen(m_color);
    painter->setBrush(m_color);
    painter->drawRect(this->boundingRect());
}

QStringList MainTabsSelection::iconsPaths() const
{
    return m_iconsPaths;
}

int MainTabsSelection::iconSize() const
{
    return m_iconSize;
}

QColor MainTabsSelection::textColor() const
{
    return m_textColor;
}

void MainTabsSelection::setIconsPaths(QStringList iconsPaths)
{
    if (m_iconsPaths == iconsPaths)
        return;

    m_iconsPaths = iconsPaths;
    emit iconsPathsChanged(iconsPaths);
}

void MainTabsSelection::setIconSize(int iconSize)
{
    if (m_iconSize == iconSize)
        return;

    m_iconSize = iconSize;
    emit iconSizeChanged(iconSize);
}

void MainTabsSelection::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

