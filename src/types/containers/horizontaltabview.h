#ifndef HORIZONTALTABVIEW_H
#define HORIZONTALTABVIEW_H

#include <QObject>
#include <QPainter>
#include "abstracttabview.h"

class HorizontalTabView : public AbstractTabView
{
        Q_OBJECT
    public:
        HorizontalTabView(QObject *parent = 0);

        virtual void paint(QPainter*) {}

    private Q_SLOTS:
        virtual void resizeAndRepositionChildrens();
        virtual void addTab(QQuickItem* item);

    public Q_SLOTS:
        virtual void moveToTab(int index);
};

#endif // HORIZONTALTABVIEW_H
