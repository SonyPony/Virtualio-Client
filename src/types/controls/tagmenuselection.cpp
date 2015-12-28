#include "tagmenuselection.h"
#include "core.h"

TagMenuSelection::TagMenuSelection(QObject *parent) : TabSelection(parent)
{
    m_signalMapper = new QSignalMapper(this);

    this->setAcceptHoverEvents(true);

    connect(m_signalMapper, QSIGNAL(QSignalMapper, mapped, (int)), this, &TagMenuSelection::tabSelected);
    connect(this, &TagMenuSelection::fontChanged, this, &TagMenuSelection::reinitSelectionItems);
    connect(this, &TagMenuSelection::tabLabelsChanged, this, &TagMenuSelection::reinitSelectionItems);
    connect(this, &TagMenuSelection::tabTextColorsChanged, this, &TagMenuSelection::reinitSelectionItems);
    connect(this, &TagMenuSelection::tabSelected, [this](int index) {
        for(TagMenuSelectionItem* selectionItem: m_selectionItems) {
            if(m_selectionItems.indexOf(selectionItem) != index)
                Q_EMIT selectionItem->disSelected();
        }
    });
}

void TagMenuSelection::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::TextAntialiasing);

    // draw background
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(boundingRect().adjusted(0, 0, -this->height(), 0));

    // draw end triangle
    const QPointF points[3] = {
        QPointF(this->width() - this->height(), 0),
        QPointF(this->width(), this->height()),
        QPointF(this->width() - this->height(), this->height())
    };

    painter->drawConvexPolygon(points, 3);
}

QStringList TagMenuSelection::tabTextColors() const
{
    return m_tabTextColors;
}

void TagMenuSelection::reinitSelectionItems()
{
    if(m_tabTextColors.length() != m_tabLabels.length())
        return;

    for(TagMenuSelectionItem* selectionItem: m_selectionItems) {
        m_selectionItems.removeAll(selectionItem);
        selectionItem->deleteLater();
    }

    double totalWidth = m_spacing;
    const QFontMetricsF fm(m_font);

    for(QString text: m_tabLabels) {
        const int key = m_tabLabels.indexOf(text);
        TagMenuSelectionItem* selectionItem = new TagMenuSelectionItem(text, m_tabTextColors[key], QColor("white"), this);
        connect(selectionItem, SIGNAL(selected()), m_signalMapper, SLOT(map()));

        m_signalMapper->setMapping(selectionItem, key);

        selectionItem->setParentItem(this);
        selectionItem->setWidth(fm.width(text));
        selectionItem->setHeight(this->height());
        selectionItem->setX(totalWidth);

        selectionItem->setFont(m_font);
        selectionItem->setColor(QColor("transparent"));
        selectionItem->update();

        m_selectionItems.append(selectionItem);
        totalWidth += fm.width(text) + m_spacing;
    }

    this->setWidth(totalWidth + this->height());
    this->update();
}

void TagMenuSelection::setTabTextColors(QStringList tabTexColors)
{
    if (m_tabTextColors == tabTexColors)
        return;

    m_tabTextColors = tabTexColors;
    emit tabTextColorsChanged(tabTexColors);
}

