#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H

#include <QQuickPaintedItem>

class PaintedItem : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

    protected:
        QColor m_color;

    public:
        PaintedItem(QQuickItem* parent = 0);
        virtual void paint(QPainter *painter) = 0;

        QColor color() const;

    public slots:
        void setColor(QColor color);

    signals:
        void colorChanged(QColor color);
};

#endif // PAINTEDITEM_H