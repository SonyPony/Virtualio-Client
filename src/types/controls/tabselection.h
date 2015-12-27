#ifndef TABSELECTION_H
#define TABSELECTION_H

#include <QQuickItem>
#include "painteditem.h"

class TabSelection : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QStringList tabLabels READ tabLabels WRITE setTabLabels NOTIFY tabLabelsChanged)
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

    protected:
        QFont m_font;
        QStringList m_tabLabels;
        int m_spacing;

    public:
        TabSelection(QObject* parent = 0);
        virtual void paint(QPainter *painter) = 0;

        QFont font() const;
        QStringList tabLabels() const;
        int spacing() const;

    public Q_SLOTS:
        void setFont(QFont font);
        void setTabLabels(QStringList tabLabels);
        void setSpacing(int spacing);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void tabLabelsChanged(QStringList tabLabels);
        void spacingChanged(int spacing);
        void tabSelected(int index);
};

#endif // TABSELECTION_H
