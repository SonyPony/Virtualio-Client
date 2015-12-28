#ifndef TABSSELECTION_H
#define TABSSELECTION_H

#include "tabselection.h"
#include <QQuickItem>
#include <QPainter>
#include <QList>
#include <QRect>
#include "../containers/maintabselectionitem.h"
#include <QSignalMapper>

class MainTabsSelection : public TabSelection
{
        Q_OBJECT
        Q_PROPERTY(QStringList iconsPaths READ iconsPaths WRITE setIconsPaths NOTIFY iconsPathsChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)

    private:
        QStringList m_iconsPaths;
        QColor m_textColor;
        QSignalMapper* m_signalMapper;
        int m_iconSize;
        QList<MainTabSelectionItem*> m_selectionItems;

    public:
        MainTabsSelection(QObject *parent = 0);

        virtual void paint(QPainter* painter);

        QStringList iconsPaths() const;
        int iconSize() const;

        QColor textColor() const;

    protected Q_SLOTS:
        void initSelectionItems();

    public slots:
        void setIconsPaths(QStringList iconsPaths);
        void setIconSize(int iconSize);
        void setTextColor(QColor textColor);

    signals:
        void iconsPathsChanged(QStringList iconsPaths);
        void textColorChanged(QColor textColor);
        void iconSizeChanged(int iconSize);

};


#endif // TABSSELECTION_H
