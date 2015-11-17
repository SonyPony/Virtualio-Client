#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H

#include "abstractbutton.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMouseEvent>
#include <QHoverEvent>

class StyledButton : public AbstractButton
{
        Q_OBJECT
        Q_PROPERTY(QColor _backgroundColor READ _backgroundColor WRITE _setBackgroundColor NOTIFY _backgroundColorChanged)

    private:
        QColor m_backgroundColor;
        QPropertyAnimation* m_colorAnimation;
        QPropertyAnimation* m_textColorAnimation;
        QPropertyAnimation* m_backgroundColorAnimation;
        QParallelAnimationGroup* m_hoverAnimation;

    protected:
        virtual void hoverEnterEvent(QHoverEvent* event);
        virtual void hoverLeaveEvent(QHoverEvent* event);

    public:
        StyledButton(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QColor _backgroundColor() const;

    private slots:
        void invertColors();

    public slots:
        void _setBackgroundColor(QColor _backgroundColor);

    signals:
        void _backgroundColorChanged(QColor _backgroundColor);
};

#endif // STYLEDBUTTON_H
