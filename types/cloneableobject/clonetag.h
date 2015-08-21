#ifndef CLONEDTAG_H
#define CLONEDTAG_H

#include <QPainter>
#include "cloneobject.h"

class CloneTag : public CloneObject
{
    Q_OBJECT

    protected:
        //virtual void dragEnterEvent(QDragEnterEvent* event);

    public:
        CloneTag();
        CloneTag(int index, QObject* parent);

        virtual void paint(QPainter* painter);
};

#endif // CLONEDTAG_H
