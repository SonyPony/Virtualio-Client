#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "painteditem.h"
#include <QPainter>
#include "../controls/scrollbar.h"

class ScrollView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    private:
        QQuickItem* m_item;
        ScrollBar* m_horizontalScrollBar;
        ScrollBar* m_verticalScrollBar;
        QColor m_backgroundColor;

    public:
        ScrollView(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QColor backgroundColor() const;

    public Q_SLOTS:
        void setBackgroundColor(QColor backgroundColor);

    private Q_SLOTS:
        void checkIfHideScrollBars();
        void registerItem(QQuickItem* item);
        void updateVerticalScrollbar();
        void updateHorizontalScrollbar();

    Q_SIGNALS:
        void newItem(QQuickItem* item);
        void backgroundColorChanged(QColor backgroundColor);
};

#endif // SCROLLVIEW_H
