#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H

#include "painteditem.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMouseEvent>
#include <QHoverEvent>

class StyledButton : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor _backgroundColor READ _backgroundColor WRITE _setBackgroundColor NOTIFY _backgroundColorChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

    private:
        bool m_pressed;
        bool m_hovered;
        QColor m_textColor;
        QColor m_backgroundColor;
        QPropertyAnimation* m_colorAnimation;
        QPropertyAnimation* m_textColorAnimation;
        QPropertyAnimation* m_backgroundColorAnimation;
        QParallelAnimationGroup* m_hoverAnimation;
        QFont m_font;

    protected:
        virtual void hoverEnterEvent(QHoverEvent* event);
        virtual void hoverLeaveEvent(QHoverEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);

    public:
        StyledButton(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QColor textColor() const;
        QColor _backgroundColor() const;
        QFont font() const;

    private slots:
        void invertColors();

    public slots:
        void setTextColor(QColor textColor);
        void _setBackgroundColor(QColor _backgroundColor);
        void setFont(QFont font);

    signals:
        void clicked(QPoint position);
        void textColorChanged(QColor textColor);
        void _backgroundColorChanged(QColor _backgroundColor);
        void fontChanged(QFont font);
};

#endif // STYLEDBUTTON_H
