#ifndef MODULESCONNECTIONVIEW_H
#define MODULESCONNECTIONVIEW_H

#include "painteditem.h"
#include <QPainter>
#include "moduleconnectionpanel.h"

class ModulesConnectionView : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QStringList modulesNames READ modulesNames WRITE setModulesNames NOTIFY modulesNamesChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(int connectionTablePos READ connectionTablePos WRITE setConnectionTablePos NOTIFY connectionTablePosChanged)
        Q_PROPERTY(QColor activeColor READ activeColor WRITE setActiveColor NOTIFY activeColorChanged)
        Q_PROPERTY(QColor inactiveColor READ inactiveColor WRITE setInactiveColor NOTIFY inactiveColorChanged)
        Q_PROPERTY(QColor nameColor READ nameColor WRITE setNameColor NOTIFY nameColorChanged)

    private:
        QStringList m_modulesNames;
        QMap<QString, int> m_modulesStates;
        QMap<QString, ModuleConnectionPanel*> m_connectionPanels;
        QFont m_font;
        int m_connectionTablePos;
        QColor m_inactiveColor;
        QColor m_activeColor;
        QColor m_nameColor;

    public:
        ModulesConnectionView(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        static void registerType();

        QStringList modulesNames() const;
        QFont font() const;
        int connectionTablePos() const;
        QColor inactiveColor() const;
        QColor activeColor() const;
        QColor nameColor() const;

    private Q_SLOTS:
        void generatePanels();

    public Q_SLOTS:
        void setModuleState(QString name, int state);
        void setModulesNames(QStringList modulesNames);
        void setFont(QFont font);
        void setConnectionTablePos(int connectionTablePos);
        void setInactiveColor(QColor inactiveColor);
        void setActiveColor(QColor activeColor);
        void setNameColor(QColor nameColor);

    Q_SIGNALS:
        void modulesNamesChanged(QStringList modulesNames);
        void fontChanged(QFont font);
        void connectionTablePosChanged(int connectionTablePos);
        void inactiveColorChanged(QColor inactiveColor);
        void activeColorChanged(QColor activeColor);
        void nameColorChanged(QColor nameColor);
};

#endif // MODULESCONNECTIONVIEW_H
