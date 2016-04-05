#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <QQuickItem>
#include "hideablewidget.h"

class DropDown : public HideableWidget
{
        Q_OBJECT

    private:
        qreal m_currentY;

    protected:
        qreal currentY() const;

    public:
        DropDown(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

    protected Q_SLOTS:
        void resetY();

    public Q_SLOTS:
        virtual QQuickItem* addItem(QQuickItem* item);

    Q_SIGNALS:
};

#endif // DROPDOWN_H
