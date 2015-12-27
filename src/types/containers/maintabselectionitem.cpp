#include "maintabselectionitem.h"
#include <QSvgRenderer>

MainTabSelectionItem::MainTabSelectionItem(QObject *parent):
    m_iconPath(""),
    TabSelectionItem(parent)
{
    m_text = "";
    setAcceptedMouseButtons(Qt::LeftButton);
}

MainTabSelectionItem::MainTabSelectionItem(QString label, QString iconPath, int iconSize, QObject* parent):
    m_iconSize(iconSize),
    m_iconPath(iconPath),
    TabSelectionItem(parent)
{
    m_text = label;
    setAcceptedMouseButtons(Qt::LeftButton);
}

void MainTabSelectionItem::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    // draw background
    painter->setPen(m_color);
    painter->setBrush(m_color);
    painter->drawRect(this->boundingRect());

    // stuff for painting icons
    QSvgRenderer svgRenderer;
    svgRenderer.load(m_iconPath);

    // size of icon
    // every icon has different proportion -> need to get bigger side and change the another one to save side ratio
    const double resizeRatio = (double)m_iconSize / qMax(svgRenderer.defaultSize().width(), svgRenderer.defaultSize().height());
    const QSizeF resizedSize = svgRenderer.defaultSize() * resizeRatio;

    // stuff for positioning text
    const QFontMetrics fm(m_font);
    const double spacing = m_font.pixelSize() / 3.;
    const double space = (this->height() - resizedSize.height() - spacing - (double)fm.height()) / 2.;
    const double textY = this->height() - space - fm.height();

    // position of icon
    const QPointF iconPos(
        (this->width() - resizedSize.width()) / 2.,
        space
    );

    // draw icon
    svgRenderer.render(painter, QRectF(iconPos, resizedSize));

    // draw label
    painter->setPen(m_textColor);
    painter->setBrush(m_textColor);
    painter->setFont(m_font);
    painter->drawText(QRectF(0, textY, this->width(), this->height() - textY),
                      Qt::AlignHCenter,
                      m_text);
}

QString MainTabSelectionItem::iconPath() const
{
    return m_iconPath;
}

int MainTabSelectionItem::iconSize() const
{
    return m_iconSize;
}

void MainTabSelectionItem::setIconPath(QString iconPath)
{
    if (m_iconPath == iconPath)
        return;

    m_iconPath = iconPath;
    emit iconPathChanged(iconPath);
}

void MainTabSelectionItem::setIconSize(int iconSize)
{
    if (m_iconSize == iconSize)
        return;

    m_iconSize = iconSize;
    emit iconSizeChanged(iconSize);
}

