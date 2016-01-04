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

    private:
        void init();

    protected:
        CloneManager<CloneTag> *m_manager;
        TagAppearance* m_tagAppearance;
        QPropertyAnimation* m_opacityAnimation;

    public:
        CloneableTag(ExtentedEnums::Direction direction = ExtentedEnums::Right, QObject* parent = 0);
        CloneableTag(QString name, QColor firstColor, QColor secondColor, QColor focusColor, ExtentedEnums::Direction direction = ExtentedEnums::Right, QObject* parent = 0);
        TagAppearance* appearance();

        virtual void paint(QPainter* painter);
        virtual void mousePressEvent(QMouseEvent*);

    private Q_SLOTS:
        void resizeAppearance();

    public Q_SLOTS:
        void fadeIn();
        void fadeOut();

    Q_SIGNALS:
        void newObject(CloneTag* object);
};

#endif // CLONEABLETAG_H
