#ifndef AbstractGraphContent_H
#define AbstractGraphContent_H

#include "../resizeableitem.h"
#include "core/interval.h"
#include "graphaxis.h"

class AbstractGraphContent : public ResizeAbleItem
{
        Q_OBJECT
        Q_PROPERTY(QList<double> dataX READ dataX WRITE setDataX NOTIFY dataXChanged)
        Q_PROPERTY(QList<double> dataY READ dataY WRITE setDataY NOTIFY dataYChanged)
        Q_PROPERTY(GraphAxis* verticalAxis READ verticalAxis WRITE setVerticalAxis NOTIFY verticalAxisChanged)
        Q_PROPERTY(GraphAxis* horizontalAxis READ horizontalAxis WRITE setHorizontalAxis NOTIFY horizontalAxisChanged)

    protected:
        QList<double> m_dataX;
        QList<double> m_dataY;
        GraphAxis* m_verticalAxis;
        GraphAxis* m_horizontalAxis;

    public:
        AbstractGraphContent();

        virtual void paint(QPainter*) = 0;

        QList<double> dataX() const;
        QList<double> dataY() const;
        GraphAxis* verticalAxis() const;
        GraphAxis* horizontalAxis() const;

    private slots:
        void setHeightSameAsAxis();
        void setWidthSameAsAxis();

    public slots:
        void setDataX(QList<double> dataX);
        void setDataY(QList<double> dataY);

        void setVerticalAxis(GraphAxis* verticalAxis);
        void setHorizontalAxis(GraphAxis* horizontalAxis);

    signals:
        void dataXChanged(QList<double> dataX);
        void dataYChanged(QList<double> dataY);
        void verticalAxisChanged(GraphAxis* verticalAxis);
        void horizontalAxisChanged(GraphAxis* horizontalAxis);
};

#endif // AbstractGraphContent_H
