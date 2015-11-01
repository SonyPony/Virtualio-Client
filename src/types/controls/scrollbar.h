#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "noninteractivescrollbar.h"
#include <QPainter>
#include <QMouseEvent>
#include "draganddropmanager.h"

class ScrollBar : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
        Q_PROPERTY(double ratio READ ratio WRITE setRatio NOTIFY ratioChanged)
        Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

    private:
        NonInteractiveScrollBar* m_nonInteractiveScrollBar;
        DragAndDropManager* m_dragAndDropManager;
        QColor m_backgroundColor;
        double m_ratio;
        int m_orientation;

    protected:
        virtual void mousePressEvent(QMouseEvent* e);
        virtual void mouseMoveEvent(QMouseEvent* e);
        virtual void mouseReleaseEvent(QMouseEvent* e);

    public:
        ScrollBar(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QColor backgroundColor() const;
        double ratio() const;
        int orientation() const;

    private Q_SLOTS:
        void updateScrollBarSize();

    public Q_SLOTS:
        void setBackgroundColor(QColor backgroundColor);
        void setRatio(double ratio);
        void setOrientation(int orientation);

    Q_SIGNALS:
        void backgroundColorChanged(QColor backgroundColor);
        void ratioChanged(double ratio);
        void orientationChanged(int orientation);
};

#endif // SCROLLBAR_H
