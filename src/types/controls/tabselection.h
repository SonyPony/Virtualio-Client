#ifndef TABSELECTION_H
#define TABSELECTION_H

#include <QQuickItem>
#include "abstracttabselection.h"

class TabSelection : public AbstractTabSelection
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QStringList tabLabels READ tabLabels WRITE setTabLabels NOTIFY tabLabelsChanged)

    protected:
        QFont m_font;
        QStringList m_tabLabels;

    public:
        TabSelection(QObject* parent = 0);

        virtual void paint(QPainter *painter) = 0;

        QFont font() const;
        QStringList tabLabels() const;

    public Q_SLOTS:
        void setFont(QFont font);
        void setTabLabels(QStringList tabLabels);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void tabLabelsChanged(QStringList tabLabels);
};

#endif // TABSELECTION_H
