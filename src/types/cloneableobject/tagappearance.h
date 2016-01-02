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
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

    private:
        ExtentedEnums::Direction m_currentDirection;
        QPropertyAnimation* m_bodyMoveAnimation;
        QRectF m_body;
        QPoint m_bodyPosition;
        QColor m_firstColor;
        QColor m_secondColor;
        QString m_name;
        QColor m_textColor;
        QFont m_font;

    public:
        TagAppearance(QString name, QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction, QQuickItem* parent = 0);
        TagAppearance(TagAppearance* other, QQuickItem *parent = 0);

        //hack - paint parent over children
        virtual void paint(QPainter*) {}
        void paintTag(QPainter *painter);

        QRectF body() const;

        QPoint bodyPosition() const;
        QColor firstColor() const;
        QColor secondColor() const;
        ExtentedEnums::Direction currentDirection() const;
        QString name() const;
        QColor textColor() const;
        QFont font() const;

    private slots:
        void setBodySize();
        void updatePaintTag();
        void setBodyPosition();

    public slots:
        void setBodyPosition(QPoint bodyPosition);
        void pointTo(ExtentedEnums::Direction direction);
        void setName(QString name);
        void setTextColor(QColor textColor);
        void setFont(QFont font);

    signals:
        void requestUpdate();
        void bodyPositionChanged(QPoint bodyPosition);
        void nameChanged(QString name);
        void textColorChanged(QColor textColor);
        void fontChanged(QFont font);
};

#endif // TAGAPPEARANCE_H
