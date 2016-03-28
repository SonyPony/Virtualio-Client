#include "recentprojectsview.h"
#include <QRegularExpression>
#include <QFileInfo>

RecentProjectsView::RecentProjectsView(QQuickItem *parent): PaintedItem(parent)
{
    m_signalMapper = new QSignalMapper(this);

    connect(m_signalMapper, SIGNAL(mapped(QString)), this, SLOT(emitProjectSelection(QString)));
    connect(this, &RecentProjectsView::titleColorChanged, this, &QQuickItem::update);
    connect(this, &RecentProjectsView::fontChanged, this, &QQuickItem::update);
}

void RecentProjectsView::paint(QPainter *painter)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    painter->setFont(m_font);
    painter->setBrush(m_color);
    painter->setPen(m_color);

    painter->drawRect(this->boundingRect());

    QRectF rect = this->boundingRect();
    rect.setLeft(m_font.pixelSize() / 2.);
    rect.setTop(m_font.pixelSize() / 2.);
    painter->setPen(m_titleColor);
    painter->setBrush(m_titleColor);
    painter->drawText(rect, Qt::AlignTop | Qt::AlignLeft, tr("Recent projects"));
}

void RecentProjectsView::registerType()
{
    qmlRegisterType<RecentProjectsView>("RecentProjectsView", 1, 0, "RecentProjectsView");
}

QColor RecentProjectsView::titleColor() const
{
    return m_titleColor;
}

QFont RecentProjectsView::font() const
{
    return m_font;
}

QFont RecentProjectsView::linksFont() const
{
    return m_linksFont;
}

void RecentProjectsView::loadRecentProjects()
{
    QFile log(m_logName);
    if(!log.exists()) {
        m_recentProjects = QStringList();
        return;
    }

    else {
        if(log.open(QIODevice::ReadOnly)) {
            QString rawData = log.readAll();
            log.close();

            m_recentProjects = rawData.split("\n");
            m_recentProjects.removeAll("");
            qDebug() << m_recentProjects;
            this->generateLinks();
        }

        else
            Q_ASSERT_X(false, "Recent projects", "Undefined error");
    }
}

void RecentProjectsView::save()
{
    QFile log(m_logName);
    QString finalPath;

    if(log.open(QIODevice::WriteOnly)) {
        for(const QString& path: m_recentProjects) {
            finalPath = path;
            log.write(finalPath.append('\n').toLocal8Bit());
        }

        log.close();
    }
}

void RecentProjectsView::generateLinks()
{
    ClickableText* link = NULL;
    for(const QString& projectPath: m_recentProjects) {
        QFileInfo fileInfo(projectPath);
        link = new ClickableText(this);
        link->setParentItem(this);

        link->setX(m_font.pixelSize() / 2.);
        link->setHeight(40);
        link->setY(m_font.pixelSize() * 1.5 + m_recentProjects.indexOf(projectPath) * link->height() + 15);
        link->setText(fileInfo.baseName());
        link->setDescription(projectPath);
        link->setDescriptionColor(QColor("white"));
        link->setBackgroundColor(QColor("transparent"));
        link->setShowDescription(true);
        link->setFont(m_linksFont);
        link->setColor(m_titleColor);

        m_signalMapper->setMapping(link, projectPath);
        connect(link, SIGNAL(clicked(QPoint)), m_signalMapper, SLOT(map()));

        m_links.append(link);
    }
}

void RecentProjectsView::emitProjectSelection(QString path)
{
    Q_EMIT this->projectSelected(QUrl(path));
}

void RecentProjectsView::setTitleColor(QColor titleColor)
{
    if (m_titleColor == titleColor)
        return;

    m_titleColor = titleColor;
    emit titleColorChanged(titleColor);
}

void RecentProjectsView::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void RecentProjectsView::addProjectPath(QString path)
{
    path.remove(QRegularExpression("^file:///"));
    if(m_recentProjects.contains(path))
        m_recentProjects.removeAll(path);
    else if(m_recentProjects.length() == m_maxCount)
        m_recentProjects.removeLast();

    m_recentProjects.prepend(path);
    this->save();
}

void RecentProjectsView::setLinksFont(QFont linksFont)
{
    if (m_linksFont == linksFont)
        return;

    m_linksFont = linksFont;
    emit linksFontChanged(linksFont);
}

