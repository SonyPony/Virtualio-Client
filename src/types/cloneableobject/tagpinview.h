#ifndef TAGPINVIEW_H
#define TAGPINVIEW_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "../animations/moveanimation.h"

class TagPinView : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    private:
        QString m_pinNumber;
        QColor m_color;
        QColor m_textColor;

    public:
        TagPinView(QQuickItem* parent = 0);

        virtual void paint(QPainter*) {}
        void paintPinView(QPainter* painter);

        QColor color() const;
        QColor textColor() const;

    public slots:
        void setPinNumber(int pin);
        void setColor(QColor color);
        void setTextColor(QColor textColor);

    signals:
        void colorChanged(QColor color);
        void textColorChanged(QColor textColor);
};

#endif // TAGPINVIEW_H
