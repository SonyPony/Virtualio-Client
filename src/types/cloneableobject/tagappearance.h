#ifndef TAGAPPEARANCE_H
#define TAGAPPEARANCE_H

#include <QQuickPaintedItem>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include <QPainter>
#include "core.h"

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
        TagAppearance(QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction, QQuickItem* parent = 0);
        TagAppearance(TagAppearance* other, QQuickItem *parent = 0);

        //hack - paint parent over children
        virtual void paint(QPainter*) {}
        void paintTag(QPainter *painter);

        QRectF body() const;

        QPoint bodyPosition() const;
        QColor firstColor() const;
        QColor secondColor() const;
        ExtentedEnums::Direction currentDirection() const;

    private slots:
        void setBodySize();
        void updatePaintTag();
        void setBodyPosition();

    public slots:
        void setBodyPosition(QPoint bodyPosition);
        void pointTo(ExtentedEnums::Direction direction);

    signals:
        void requestUpdate();
        void bodyPositionChanged(QPoint bodyPosition);
};

#endif // TAGAPPEARANCE_H
