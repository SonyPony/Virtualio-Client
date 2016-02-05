#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QPainter>
#include <QQuickItem>
#include <QPropertyAnimation>
#include "painteditem.h"

class ModalDialog : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QSize dialogBaseSize READ dialogBaseSize WRITE setDialogBaseSize NOTIFY dialogBaseSizeChanged)
        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
        Q_PROPERTY(double backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity NOTIFY backgroundOpacityChanged)
        Q_PROPERTY(QQuickItem* container READ container CONSTANT)

    private:
        QPropertyAnimation* m_baseOpacityAnimation;

    protected:
        QQuickItem* m_container;
        double m_backgroundOpacity;
        QSize m_dialogBaseSize;
        QColor m_backgroundColor;

        virtual void mousePressEvent(QMouseEvent*) {}

    public:
        ModalDialog(QQuickItem* parent = 0);

        virtual void paint(QPainter *painter);

        QSize dialogBaseSize() const;
        QColor backgroundColor() const;
        double backgroundOpacity() const;
        QQuickItem* container() const;

    private Q_SLOTS:
        void registerChildren();
        void centerContainer();

    public Q_SLOTS:
        void setDialogBaseSize(QSize dialogBaseSize);
        void setBackgroundColor(QColor backgroundColor);
        void setBackgroundOpacity(double backgroundOpacity);
        void hide();
        void show();

    Q_SIGNALS:
        void dialogBaseSizeChanged(QSize dialogBaseSize);
        void backgroundColorChanged(QColor backgroundColor);
        void backgroundOpacityChanged(double backgroundOpacity);
        void showed();
        void hided();
};

#endif // MODALDIALOG_H
