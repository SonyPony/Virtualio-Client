#ifndef TAGAPPEARANCE_H
#define TAGAPPEARANCE_H

#include <QQuickPaintedItem>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include <QPainter>
#include "../../core/core.h"

class TagAppearance : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QPoint bodyPosition READ bodyPosition WRITE setBodyPosition NOTIFY bodyPositionChanged)

    private:
        ExtentedEnums::Direction m_currentDirection;
        QPropertyAnimation* m_bodyMoveAnimation;
        QRectF m_body;
        QPoint m_bodyPosition;
        QColor m_firstColor;
        QColor m_secondColor;

    public:
        TagAppearance(QColor firstColor, QColor secondColor, QQuickItem* parent = 0);
        TagAppearance(TagAppearance* other, QQuickItem *parent = 0);

        //hack - paint parent over children
        virtual void paint(QPainter *painter) {}
        void paintTag(QPainter *painter);

        QRectF body() const;

        QPoint bodyPosition() const;
        QColor firstColor() const;
        QColor secondColor() const;

    private slots:
        void resizeAppearance();
        void setBodySize();
        void updatePaintTag();

    public slots:
        void setBodyPosition(QPoint bodyPosition);
        void pointTo(ExtentedEnums::Direction direction);

    signals:
        void requestUpdate();
        void bodyPositionChanged(QPoint bodyPosition);
};

#endif // TAGAPPEARANCE_H
