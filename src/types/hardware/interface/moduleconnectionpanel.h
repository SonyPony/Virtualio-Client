#ifndef MODULECONNECTIONPANEL_H
#define MODULECONNECTIONPANEL_H

#include "painteditem.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <types/animations/textchangeanimation.h>

class ModuleState: public QObject {
        Q_OBJECT
        Q_ENUMS(State)

    public:
        enum State {
            Discconnected = 0,
            Connected = 1
        };
};

class ModuleConnectionPanel : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor NOTIFY activeColorChanged)
        Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor NOTIFY inactiveColorChanged)
        Q_PROPERTY(QString moduleName READ moduleName WRITE setModuleName NOTIFY moduleNameChanged)
        Q_PROPERTY(int connectionStatePos READ connectionStatePos WRITE setConnectionStatePos NOTIFY connectionStatePosChanged)
        Q_PROPERTY(int connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)
        Q_PROPERTY(QColor __stateColor READ __stateColor WRITE __setStateColor NOTIFY __stateColorChanged)
        Q_PROPERTY(QColor nameColor READ nameColor WRITE setNameColor NOTIFY nameColorChanged)

    private:
        QFont m_font;
        QColor m_activeColor;
        QColor m_inactiveColor;
        QString m_moduleName;
        int m_connectionStatePos;
        int m_connectionState;
        QColor m_nameColor;
        QPropertyAnimation* m_colorAnimation;
        QColor p_stateColor;
        TextChangeAnimation* m_textAnimation;

    public:
        ModuleConnectionPanel(QQuickItem* parent);

        virtual void paint(QPainter* painter);

        QFont font() const;
        QColor activeColor() const;
        QColor inactiveColor() const;
        QString moduleName() const;
        int connectionStatePos() const;
        int connectionState() const;
        QColor __stateColor() const;
        QColor nameColor() const;

    private Q_SLOTS:
        void startTextAnimation(int newConnectionState);
        void startColorAnimation(int newConnectionState);

    public Q_SLOTS:
        void setFont(QFont font);
        void setActiveColor(QColor activeColor);
        void setInactiveColor(QColor inactiveColor);
        void setModuleName(QString moduleName);
        void setConnectionStatePos(int connectionStatePos);
        void setConnectionState(int connectionState);
        void __setStateColor(QColor __stateColor);
        void setNameColor(QColor nameColor);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void activeColorChanged(QColor activeColor);
        void inactiveColorChanged(QColor inactiveColor);
        void moduleNameChanged(QString moduleName);
        void connectionStatePosChanged(int connectionStatePos);
        void connectionStateChanged(int connectionState);
        void __stateColorChanged(QColor __stateColor);
        void nameColorChanged(QColor nameColor);
};

#endif // MODULECONNECTIONPANEL_H
