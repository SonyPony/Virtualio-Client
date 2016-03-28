#ifndef RECENTPROJECTSVIEW_H
#define RECENTPROJECTSVIEW_H

#include "painteditem.h"
#include <QPainter>
#include <types/controls/clickabletext.h>
#include <QSignalMapper>

class RecentProjectsView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QFont linksFont READ linksFont WRITE setLinksFont NOTIFY linksFontChanged)

    private:
        static constexpr char* m_logName = "recentprojects.txt";
        QStringList m_recentProjects;
        QColor m_titleColor;
        QFont m_font;
        QList<ClickableText*> m_links;
        QFont m_linksFont;
        QSignalMapper* m_signalMapper;

        static constexpr int m_maxCount = 12;

    public:
        RecentProjectsView(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        static void registerType();

        QColor titleColor() const;
        QFont font() const;
        QFont linksFont() const;

    private Q_SLOTS:
        void save();
        void generateLinks();
        void emitProjectSelection(QString path);

    public Q_SLOTS:
        void loadRecentProjects();
        void setTitleColor(QColor titleColor);
        void setFont(QFont font);
        void addProjectPath(QString path);
        void setLinksFont(QFont linksFont);

    Q_SIGNALS:
        void titleColorChanged(QColor titleColor);
        void fontChanged(QFont font);
        void linksFontChanged(QFont linksFont);
        void projectSelected(QUrl path);
};

#endif // RECENTPROJECTSVIEW_H
