#ifndef TABSELECTIONITEM_H
#define TABSELECTIONITEM_H

#include <QQuickItem>
#include "painteditem.h"

class TabSelectionItem : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    protected:
        QString m_text;
        QColor m_textColor;
        QFont m_font;

        virtual void mousePressEvent(QMouseEvent*);

    public:
        TabSelectionItem(QObject* parent = 0);

        virtual void paint(QPainter*) {}

        QString text() const;
        QColor textColor() const;
        QFont font() const;

    public Q_SLOTS:
        void setText(QString text);
        void setTextColor(QColor textColor);
        void setFont(QFont font);

    Q_SIGNALS:
        void textChanged(QString text);
        void textColorChanged(QColor textColor);
        void fontChanged(QFont font);
        void selected();
};

#endif // TABSELECTIONITEM_H
