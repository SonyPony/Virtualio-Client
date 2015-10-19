#ifndef VERTICALTABVIEW_H
#define VERTICALTABVIEW_H

#include "abstracttabview.h"
#include <QQuickItem>

class VerticalTabView : public AbstractTabView
{
        Q_OBJECT
    public:
        VerticalTabView(QQuickItem* parent = 0);

        virtual void paint(QPainter*) {}

    private slots:
        virtual void resizeAndRepositionChildrens();

    public slots:
        virtual void moveToTab(int index);
};

#endif // VERTICALTABVIEW_H
