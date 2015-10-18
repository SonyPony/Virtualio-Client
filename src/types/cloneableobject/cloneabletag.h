#ifndef CLONEABLETAG_H
#define CLONEABLETAG_H

#include "clonemanager.h"
#include "clonetag.h"
#include "tagappearance.h"
#include "painteditem.h"
#include <QQuickPaintedItem>
#include <QPainter>
#include <QList>

class CloneableTag : public PaintedItem
{
        Q_OBJECT

    protected:
        CloneManager<CloneTag> *m_manager;
        TagAppearance* m_tagAppearance;

    public:
        CloneableTag();

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent*);

    private slots:
        void resizeAppearance();

    signals:
        void newObject(CloneTag* object);
};

#endif // CLONEABLETAG_H
