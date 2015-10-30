#include "tabsselection.h"
#include <QImage>
#include <QPoint>
#include <QSvgRenderer>
#include <QFontMetrics>

TabsSelection::TabsSelection(QQuickItem *parent): PaintedItem(parent), m_spacing(0)
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

void TabsSelection::mousePressEvent(QMouseEvent *event)
{
    for(const QRect& clickableArea: m_clickableAreas)
        if(clickableArea.contains(event->pos()))
            emit tabSelected(m_clickableAreas.indexOf(clickableArea));
}

void TabsSelection::updateClickableArea(int index, QPoint point, QSize size)
{
    //extend list if index is not defined
    if(index >= m_clickableAreas.size()) {
        for(int i = m_clickableAreas.size(); i < index + 1; i++)
            m_clickableAreas.append(QRect());
    }

    m_clickableAreas[index] = QRect(point, QSize(width(), size.height()));
}

void TabsSelection::paint(QPainter *painter)
{
    // draw background
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->setBrush(m_color);
    painter->setPen(m_color);
    painter->drawRect(boundingRect());

    QSvgRenderer svgRenderer;
    double currentPos = m_font.pixelSize();
    QFontMetrics fontMetrics(m_font);

    for(const QString& iconPath: m_iconsPaths) {
        const int key = m_iconsPaths.indexOf(iconPath);

        if(svgRenderer.load(iconPath)) {
            //update clickable areas
            updateClickableArea(key,
                                QPoint(0, currentPos),
                                QSize(
                                    svgRenderer.defaultSize().width(),
                                    svgRenderer.defaultSize().height() + m_font.pixelSize() * 1.5)
                                );

            // draw tab icon
            int centerPos = (width() - svgRenderer.defaultSize().width()) / 2.;
            svgRenderer.render(painter, QRect(QPoint(centerPos, currentPos), svgRenderer.defaultSize()));
            currentPos += svgRenderer.defaultSize().height() + m_font.pixelSize() / 2.;

            // draw tab label
            painter->setPen(m_textColor);

            if(key < m_tabLabels.size()) {
                painter->drawText(QRectF(0, currentPos, width(), m_font.pixelSize()),
                                  Qt::AlignHCenter,
                                  m_tabLabels[key]);
            }
            currentPos += m_spacing;
        }
    }
}

QStringList TabsSelection::iconsPaths() const
{
    return m_iconsPaths;
}

QStringList TabsSelection::tabLabels() const
{
    return m_tabLabels;
}

QFont TabsSelection::font() const
{
    return m_font;
}

int TabsSelection::spacing() const
{
    return m_spacing;
}

QColor TabsSelection::textColor() const
{
    return m_textColor;
}

int TabsSelection::iconSize() const
{
    return m_iconSize;
}

void TabsSelection::setIconsPaths(QStringList iconsPaths)
{
    if (m_iconsPaths == iconsPaths)
        return;

    m_iconsPaths = iconsPaths;
    emit iconsPathsChanged(iconsPaths);
}

void TabsSelection::setTabLabels(QStringList tabLabels)
{
    if (m_tabLabels == tabLabels)
        return;

    m_tabLabels = tabLabels;
    emit tabLabelsChanged(tabLabels);
}

void TabsSelection::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void TabsSelection::setSpacing(int spacing)
{
    if (m_spacing == spacing)
        return;

    m_spacing = spacing;
    emit spacingChanged(spacing);
}

void TabsSelection::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(textColor);
}

void TabsSelection::setIconSize(int iconSize)
{
    if (m_iconSize == iconSize)
        return;

    m_iconSize = iconSize;
    emit iconSizeChanged(iconSize);
}

