#ifndef ABSTRACTTABSELECTION_H
#define ABSTRACTTABSELECTION_H

#include <QQuickItem>
#include "painteditem.h"

class AbstractTabSelection : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

    protected:
        int m_spacing;

    public:
        AbstractTabSelection(QQuickItem* parent = 0);

        int spacing() const;

    public slots:
        void setSpacing(int spacing);

    Q_SIGNALS:
        void tabSelected(int index);
        void spacingChanged(int spacing);
};

#endif // ABSTRACTTABSELECTION_H
