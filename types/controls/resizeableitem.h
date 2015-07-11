#ifndef RESIZEABLEITEM_H
#define RESIZEABLEITEM_H

#include <QQuickPaintedItem>

class ResizeAbleItem : public QQuickPaintedItem
{
        Q_OBJECT
        Q_PROPERTY(double verticalRatio READ verticalRatio WRITE setVerticalRatio NOTIFY verticalRatioChanged)
        Q_PROPERTY(double horizontalRatio READ horizontalRatio WRITE setHorizontalRatio NOTIFY horizontalRatioChanged)

    protected:
        double m_verticalRatio;
        double m_horizontalRatio;

    public:
        ResizeAbleItem();

        virtual void paint(QPainter*) = 0;

        double verticalRatio() const;
        double horizontalRatio() const;

    public slots:
        void setVerticalRatio(double verticalRatio);
        void setHorizontalRatio(double horizontalRatio);

    signals:
        void verticalRatioChanged(double verticalRatio);
        void horizontalRatioChanged(double horizontalRatio);
};

#endif // RESIZEABLEITEM_H
