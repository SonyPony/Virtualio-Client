#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <QObject>
#include "abstractbutton.h"

class TextButton : public AbstractButton
{
        Q_OBJECT
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    protected:
        QFont m_font;
        QColor m_textColor;
        QString m_text;

    public:
        TextButton(QQuickItem *parent = 0);

        virtual void paint(QPainter*) = 0;

        QFont font() const;
        QColor textColor() const;
        QString text() const;

    public Q_SLOTS:
        void setFont(QFont font);
        void setTextColor(QColor textColor);
        void setText(QString text);

    Q_SIGNALS:
        void fontChanged(QFont font);
        void textColorChanged(QColor textColor);
        void textChanged(QString text);
};

#endif // TEXTBUTTON_H
