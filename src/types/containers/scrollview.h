#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "painteditem.h"
#include <QPainter>
#include "../controls/scrollbar.h"

class ScrollView : public PaintedItem
{
        Q_OBJECT

    private:
        QQuickItem* m_item;
        ScrollBar* m_horizontalScrollBar;
        ScrollBar* m_verticalScrollBar;

    public:
        ScrollView(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

    private Q_SLOTS:
        void registerItem(QQuickItem* item);
        void updateVerticalScrollbar();
        void updateHorizontalScrollbar();

    Q_SIGNALS:
        void newItem(QQuickItem* item);
};

#endif // SCROLLVIEW_H
