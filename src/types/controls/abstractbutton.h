#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "painteditem.h"
#include <QMouseEvent>
#include <QHoverEvent>

class AbstractButton : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    protected:
        QFont m_font;
        QColor m_textColor;
        QString m_text;
        bool m_pressed;
        bool m_hovered;

        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void hoverEnterEvent(QHoverEvent* event);
        virtual void hoverLeaveEvent(QHoverEvent* event);

    public:
        AbstractButton(QQuickItem* parent = 0);

        virtual void paint(QPainter*) = 0;

        QFont font() const;
        QColor textColor() const;
        QString text() const;

    public Q_SLOTS:
        void setFont(QFont font);
        void setTextColor(QColor textColor);
        void setText(QString text);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void textColorChanged(QColor textColor);
        void textChanged(QString text);
        void clicked(QPoint position);
        void entered();
        void leaved();
};

#endif // ABSTRACTBUTTON_H
