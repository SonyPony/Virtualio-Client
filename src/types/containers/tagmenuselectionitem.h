#ifndef TAGMENUSELECTIONITEM_H
#define TAGMENUSELECTIONITEM_H

#include <QObject>
#include <QPainter>
#include <QPropertyAnimation>
#include "tabselectionitem.h"

class TagMenuSelectionItem : public TabSelectionItem
{
        Q_OBJECT
        Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY defaultColorChanged)
        Q_PROPERTY(QColor __textColor READ __textColor WRITE __setTextColor NOTIFY __textColorChanged)

    private:
        QColor m_defaultColor;
        QPropertyAnimation* m_textColorAnimation;
        QColor p_textColor;
        bool m_selected;

        void init();

    protected:
        void invertTextColors(bool hovered);

        virtual void hoverEnterEvent(QHoverEvent*);
        virtual void hoverLeaveEvent(QHoverEvent*);

    public:
        TagMenuSelectionItem(QObject *parent = 0);
        TagMenuSelectionItem(QString text, QColor color, QColor defaultColor, QObject *parent = 0);

        virtual void paint(QPainter* painter);

        QColor defaultColor() const;
        QColor __textColor() const;

    public Q_SLOTS:
        void setDefaultColor(QColor defaultColor);
        void __setTextColor(QColor __textColor);

    Q_SIGNALS:
        void disSelected();
        void hoveredChanged(bool hovered);
        void defaultColorChanged(QColor defaultColor);
        void __textColorChanged(QColor __textColor);
};

#endif // TAGMENUSELECTIONITEM_H
