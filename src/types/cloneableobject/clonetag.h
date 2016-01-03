#ifndef CLONEDTAG_H
#define CLONEDTAG_H

#include <QPainter>
#include <QPropertyAnimation>
#include <QLinearGradient>
#include "cloneobject.h"
#include "core.h"
#include "tagappearance.h"
#include "tagpinview.h"
#include "../animations/moveanimation.h"

class CloneTag : public CloneObject
{
        Q_OBJECT
        Q_PROPERTY(QVariantMap options READ options WRITE setOptions NOTIFY optionsChanged)
        Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)

    private:
        QPropertyAnimation* m_pinViewMoveAnimation;
        QPropertyAnimation* m_opacityAnimation;
        int m_currentPinNumber;
        ExtentedEnums::Direction m_currentDirection;
        TagAppearance* m_tagAppearance;
        TagPinView* m_tagPinView;
        QVariantMap m_options;
        bool m_selected;

    public:
        CloneTag(int index, TagAppearance *appearance, QQuickItem *parent);
        ~CloneTag() {}

        virtual void paint(QPainter* painter);

        QVariantMap options() const;
        TagAppearance* appearance() const;
        bool selected() const;

    private slots:
        void repostionPinView();
        void showPinView();
        void hidePinView();
        void repositionBody(ExtentedEnums::Direction direction);
        void resize();

    public slots:
        virtual void enteredIntoGrid();
        virtual void leavedFromGrid();

        void setCurrentPinNumber(int pinNumber);
        void pointTo(ExtentedEnums::Direction direction);
        void setOptions(QVariantMap options);
        void setSelected(bool selected);

    signals:
        void currentPinNumberChanged(int value);
        void matrixPositionChanged(QPoint matrixPos, CloneTag* object);
        void directionChanged();
        void optionsChanged(QVariantMap options);
        void selectedChanged(bool selected);
};


#endif // CLONEDTAG_H
