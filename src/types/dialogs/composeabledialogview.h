#ifndef COMPOSEABLEDIALOGVIEW_H
#define COMPOSEABLEDIALOGVIEW_H

#include <QPainter>
#include <QQuickItem>
#include <painteditem.h>
#include <types/animations/moveanimation.h>

class ComposeableDialogView : public PaintedItem
{
        Q_OBJECT
    private:
        MoveAnimation* m_moveAnimation;
        QPointF m_showPos;
        QPointF m_hidePos;

    public:
        ComposeableDialogView(QQuickItem *parent = 0);
        ComposeableDialogView(QPointF showPos, QPointF hidePos, QQuickItem *parent = 0);

        virtual void paint(QPainter* painter);

    private Q_SLOTS:
        void checkAnimationType();

    public Q_SLOTS:
        void setShowPosition(QPointF point);
        void setHidePosition(QPointF point);

        void show(bool animate = true);
        void hide(bool animate = true);

    Q_SIGNALS:
        void showed();
        void hided();
};

#endif // COMPOSEABLEDIALOGVIEW_H
