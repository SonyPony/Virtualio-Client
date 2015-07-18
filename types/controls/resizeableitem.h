#ifndef RESIZEABLEITEM_H
#define RESIZEABLEITEM_H

#include <QQuickPaintedItem>

class ResizeAbleItem : public QQuickPaintedItem
{
        Q_OBJECT
        Q_ENUMS(Directions)
        Q_PROPERTY(double verticalRatio READ verticalRatio WRITE setVerticalRatio NOTIFY verticalRatioChanged)
        Q_PROPERTY(double horizontalRatio READ horizontalRatio WRITE setHorizontalRatio NOTIFY horizontalRatioChanged)
        Q_PROPERTY(int enabledDirections READ enabledDirections WRITE setEnabledDirections NOTIFY enabledDirectionsChanged)

    protected:
        double m_verticalRatio;
        double m_horizontalRatio;
        int m_enabledDirections;
        int m_originHeight;

    public:
        ResizeAbleItem();

        virtual void paint(QPainter*) = 0;

        enum Directions {
            Horizontal = 1,
            Vertical = 2
        };

        double verticalRatio() const;
        double horizontalRatio() const;
        int enabledDirections() const;
        int originHeight() const;

    private slots:
        void setOriginHeight();

    public slots:
        virtual void setVerticalRatio(double verticalRatio);
        virtual void setHorizontalRatio(double horizontalRatio);
        void setEnabledDirections(int enabledDirections);

    signals:
        void verticalRatioChanged(double verticalRatio);
        void horizontalRatioChanged(double horizontalRatio);
        void enabledDirectionsChanged(int enabledDirections);
};

#endif // RESIZEABLEITEM_H
