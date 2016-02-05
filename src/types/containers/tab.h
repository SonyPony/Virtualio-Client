#ifndef TAB_H
#define TAB_H

#include <QQuickItem>
#include <QPoint>
#include "../animations/moveanimation.h"

class Tab : public QQuickItem
{
        Q_OBJECT
        Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)

    private:
        MoveAnimation* m_moveAnimation;
        int m_index;

    public:
        Tab(QQuickItem* parent = 0);

        int index() const;

    public slots:
        void setIndex(int index);
        void move(QPointF destination);

    signals:
        void indexChanged(int index);
        void hided();
        void showed();
};



#endif // TAB_H
