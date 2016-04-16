#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "painteditem.h"
#include <QPainter>
#include <QPropertyAnimation>

class InfoPanel : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

    private:
        QFont m_font;
        QColor m_textColor;
        int m_timeout;      // in miliseconds
        QString m_text;
        QTimer* m_timer;
        QPropertyAnimation* m_opacityAnimation;

    public:
        InfoPanel(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QFont font() const;
        QColor textColor() const;
        int timeout() const;

    private Q_SLOTS:
        void hide();

    public Q_SLOTS:
        void show(QString text);

        void setFont(QFont font);
        void setTextColor(QColor textColor);
        void setTimeout(int timeout);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void textColorChanged(QColor textColor);
        void timeoutChanged(int timeout);
};

#endif // INFOPANEL_H
