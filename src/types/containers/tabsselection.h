#ifndef TABSSELECTION_H
#define TABSSELECTION_H

#include "painteditem.h"
#include <QQuickItem>
#include <QPainter>
#include <QList>
#include <QRect>
#include <QMouseEvent>

class TabsSelection : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QStringList iconsPaths READ iconsPaths WRITE setIconsPaths NOTIFY iconsPathsChanged)
        Q_PROPERTY(QStringList tabLabels READ tabLabels WRITE setTabLabels NOTIFY tabLabelsChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)

    private:
        QStringList m_iconsPaths;
        QStringList m_tabLabels;
        QFont m_font;
        int m_spacing;
        QColor m_textColor;
        QList<QRect> m_clickableAreas;
        int m_iconSize;

    protected:
        void updateClickableArea(int index, QPoint point, QSize size);

        virtual void mousePressEvent(QMouseEvent* event);

    public:
        TabsSelection(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QStringList iconsPaths() const;
        QStringList tabLabels() const;
        QFont font() const;
        int spacing() const;
        QColor textColor() const;
        int iconSize() const;

    public slots:
        void setIconsPaths(QStringList iconsPaths);
        void setTabLabels(QStringList tabLabels);
        void setFont(QFont font);
        void setSpacing(int spacing);
        void setTextColor(QColor textColor);
        void setIconSize(int iconSize);

    signals:
        void iconsPathsChanged(QStringList iconsPaths);
        void tabLabelsChanged(QStringList tabLabels);
        void fontChanged(QFont font);
        void spacingChanged(int spacing);
        void textColorChanged(QColor textColor);
        void tabSelected(int index);
        void iconSizeChanged(int iconSize);

};


#endif // TABSSELECTION_H
