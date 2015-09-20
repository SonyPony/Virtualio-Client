#ifndef CLONEDTAG_H
#define CLONEDTAG_H

#include <QPainter>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include "cloneobject.h"
#include "core.h"
#include "tagappearance.h"

class CloneTag : public CloneObject
{
        Q_OBJECT

    private:
        QPropertyAnimation* m_opacityAnimation;
        int m_currentPinNumber;
        ExtentedEnums::Direction m_currentDirection;
        TagAppearance* m_tagAppearance;

    public:
        CloneTag(int index, TagAppearance *appearance, QQuickItem *parent);
        ~CloneTag() {}

        virtual void paint(QPainter* painter);

    private slots:
        void reemitMatrixPositionChanged(QPoint position);
        void resize();

    public slots:
        virtual void enteredIntoGrid();
        virtual void leavedFromGrid();

        void setCurrentPinNumber(int pinNumber);
        void pointTo(ExtentedEnums::Direction direction);

    signals:
        void currentPinNumberChanged(int value);
        void matrixPositionChanged(QPoint matrixPos, CloneTag* object);
};


#endif // CLONEDTAG_H
