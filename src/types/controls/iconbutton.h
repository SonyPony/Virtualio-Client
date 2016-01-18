#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QQuickItem>
#include "abstractbutton.h"

class IconButton : public AbstractButton
{
        Q_OBJECT
        Q_PROPERTY(QString iconPath READ iconPath WRITE setIconPath NOTIFY iconPathChanged)
        Q_PROPERTY(QString disabledIconPath READ disabledIconPath WRITE setDisabledIconPath NOTIFY disabledIconPathChanged)
        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    private:
        QString m_iconPath;
        QString m_disabledIconPath;
        bool m_enabled;

    protected:
        virtual void mousePressEvent(QMouseEvent* event) override;

    public:
        IconButton(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QString iconPath() const;
        QString disabledIconPath() const;
        bool enabled() const;

    public Q_SLOTS:
        void setIconPath(QString iconPath);
        void setDisabledIconPath(QString disabledIconPath);
        void setEnabled(bool enabled);

    Q_SIGNALS:
        void iconPathChanged(QString iconPath);
        void disabledIconPathChanged(QString disabledIconPath);
        void enabledChanged(bool enabled);
};

#endif // ICONBUTTON_H
