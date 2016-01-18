#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H

#include "textbutton.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMouseEvent>
#include <QHoverEvent>

class StyledButton : public TextButton
{
        Q_OBJECT
        Q_PROPERTY(QColor _backgroundColor READ _backgroundColor WRITE _setBackgroundColor NOTIFY _backgroundColorChanged)
        Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)

    private:
        QColor m_backgroundColor;
        QPropertyAnimation* m_colorAnimation;
        QPropertyAnimation* m_textColorAnimation;
        QPropertyAnimation* m_backgroundColorAnimation;
        QParallelAnimationGroup* m_hoverAnimation;
        QColor m_borderColor;

    protected:
        virtual void hoverEnterEvent(QHoverEvent* event);
        virtual void hoverLeaveEvent(QHoverEvent* event);

    public:
        StyledButton(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QColor _backgroundColor() const;
        QColor borderColor() const;

    private slots:
        void invertColors();

    public slots:
        void _setBackgroundColor(QColor _backgroundColor);
        void setBorderColor(QColor borderColor);

    signals:
        void _backgroundColorChanged(QColor _backgroundColor);
        void borderColorChanged(QColor borderColor);
};

#endif // STYLEDBUTTON_H
