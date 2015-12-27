#ifndef MAINTABSELECTIONITEM_H
#define MAINTABSELECTIONITEM_H

#include <QPainter>
#include <QQuickItem>
#include "tabselectionitem.h"

class MainTabSelectionItem : public TabSelectionItem
{
        Q_OBJECT
        Q_PROPERTY(QString iconPath READ iconPath WRITE setIconPath NOTIFY iconPathChanged)
        Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)

    private:
        QString m_iconPath;
        int m_iconSize;

    public:
        MainTabSelectionItem(QObject *parent = 0);
        MainTabSelectionItem(QString label, QString iconPath, int iconSize, QObject *parent = 0);

        virtual void paint(QPainter* painter);

        QString iconPath() const;
        int iconSize() const;

    public Q_SLOTS:
        void setIconPath(QString iconPath);
        void setIconSize(int iconSize);

    Q_SIGNALS:
        void iconPathChanged(QString iconPath);
        void iconSizeChanged(int iconSize);
};

#endif // MAINTABSELECTIONITEM_H
