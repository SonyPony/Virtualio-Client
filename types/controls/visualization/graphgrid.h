#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include "abstractgraphgrid.h"

class GraphGrid : public AbstractGraphGrid
{
        Q_OBJECT
    public:
        GraphGrid();

        virtual void paint(QPainter *painter);

    private slots:
        void resizeAxisX(double ratio);
        void resizeAxisY(double ratio);

    signals:
};

#endif // GRAPHGRID_H
