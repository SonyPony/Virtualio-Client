#ifndef CLONEABLETAG_H
#define CLONEABLETAG_H

#include "clonemanager.h"
#include "clonetag.h"
#include "tagappearance.h"
#include "painteditem.h"
#include <QQuickPaintedItem>
#include <QPainter>
#include <QList>

class CloneableTag : public QQuickPaintedItem
{
        Q_OBJECT

    protected:
        CloneManager<CloneTag> *m_manager;
        TagAppearance* m_tagAppearance;

    public:
        CloneableTag(ExtentedEnums::Direction direction = ExtentedEnums::Right, QObject* parent = 0);
        CloneableTag(QString name, QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction = ExtentedEnums::Right, QObject* parent = 0);

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent*);

    private slots:
        void resizeAppearance();

    signals:
        void newObject(CloneTag* object);
};

#endif // CLONEABLETAG_H
