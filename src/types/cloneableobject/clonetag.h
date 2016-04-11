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
        Q_PROPERTY(QVariantMap controlState READ controlState WRITE setControlState NOTIFY controlStateChanged)
        Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
        Q_PROPERTY(double focusOpacity READ focusOpacity WRITE setFocusOpacity NOTIFY focusOpacityChanged)
        Q_PROPERTY(int currentPinNumber READ currentPinNumber WRITE setCurrentPinNumber NOTIFY currentPinNumberChanged)

    private:
        QPropertyAnimation* m_pinViewMoveAnimation;
        QPropertyAnimation* m_opacityAnimation;
        int m_currentPinNumber;
        ExtentedEnums::Direction m_currentDirection;
        TagAppearance* m_tagAppearance;
        TagPinView* m_tagPinView;
        QVariantMap m_options;
        bool m_selected;
        double m_focusOpacity;
        QPropertyAnimation* m_focusHeartBeat;
        QVariantMap m_controlState;
        QString m_value;
        QString m_tagName;

    public:
        CloneTag(int index, TagAppearance *appearance, QQuickItem *parent);
        ~CloneTag() {}

        virtual void paint(QPainter* painter);

        QVariantMap options() const;
        TagAppearance* appearance() const;
        bool selected() const;
        double focusOpacity() const;
        int currentPinNumber() const;
        ExtentedEnums::Direction currentDirection() const;
        QString name() const;
        QVariantMap controlState() const;

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
        void setFocusOpacity(double focusOpacity);
        void setControlState(QVariantMap controlState);
        void setValue(QString value);
        void restoreName();

    signals:
        void currentPinNumberChanged(int value);
        void matrixPositionChanged(QPoint matrixPos, CloneTag* object);
        void directionChanged();
        void optionsChanged(QVariantMap options);
        void selectedChanged(bool selected);
        void focusOpacityChanged(double focusOpacity);
        void controlStateChanged(QVariantMap controlState);
        void valueChanged(QString value);
};


#endif // CLONEDTAG_H
