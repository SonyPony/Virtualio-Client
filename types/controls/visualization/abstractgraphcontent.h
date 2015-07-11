#ifndef AbstractGraphContent_H
#define AbstractGraphContent_H

#include "../resizeableitem.h"
#include "core/interval.h"

class AbstractGraphContent : public ResizeAbleItem
{
        Q_OBJECT
        Q_PROPERTY(QList<double> dataX READ dataX WRITE setDataX NOTIFY dataXChanged)
        Q_PROPERTY(QList<double> dataY READ dataY WRITE setDataY NOTIFY dataYChanged)

    protected:
        QList<double> m_dataX;
        QList<double> m_dataY;

    public:
        AbstractGraphContent();

        virtual void paint(QPainter*) = 0;

        QList<double> dataX() const;
        QList<double> dataY() const;

    public slots:
        void setDataX(QList<double> dataX);
        void setDataY(QList<double> dataY);

    signals:
        void dataXChanged(QList<double> dataX);
        void dataYChanged(QList<double> dataY);
};

#endif // AbstractGraphContent_H
