#ifndef CLONEDTAG_H
#define CLONEDTAG_H

#include <QPainter>
#include <QPropertyAnimation>
#include "cloneobject.h"

class CloneTag : public CloneObject
{
    Q_OBJECT

    private:
        QPropertyAnimation* m_opacityAnimation;

    public:
        //CloneTag();
        CloneTag(int index, QObject* parent);
        ~CloneTag() {}

        virtual void paint(QPainter* painter);

    public slots:
        virtual void enteredIntoGrid();
        virtual void leavedFromGrid();
};

#endif // CLONEDTAG_H
