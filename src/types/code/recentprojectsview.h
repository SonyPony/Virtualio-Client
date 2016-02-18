#ifndef RECENTPROJECTSVIEW_H
#define RECENTPROJECTSVIEW_H

#include "painteditem.h"
#include <QPainter>

class RecentProjectsView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

    private:
        QColor m_titleColor;
        QFont m_font;

    public:
        RecentProjectsView(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        static void registerType();

        QColor titleColor() const;
        QFont font() const;

    public Q_SLOTS:
        void setTitleColor(QColor titleColor);
        void setFont(QFont font);

    Q_SIGNALS:
        void titleColorChanged(QColor titleColor);
        void fontChanged(QFont font);
};

#endif // RECENTPROJECTSVIEW_H
