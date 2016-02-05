#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QPainter>
#include <QQuickItem>
#include "modaldialog.h"
#include "../controls/styledbutton.h"

class MessageDialog : public ModalDialog
{
        Q_OBJECT
        Q_PROPERTY(QColor buttonColor READ buttonColor WRITE setButtonColor NOTIFY buttonColorChanged)
        Q_PROPERTY(QFont buttonFont READ buttonFont WRITE setButtonFont NOTIFY buttonFontChanged)
        Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
        Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont NOTIFY titleFontChanged)
        Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
        Q_PROPERTY(QFont messageFont READ messageFont WRITE setMessageFont NOTIFY messageFontChanged)

    private:
        StyledButton* m_button;
        QColor m_buttonColor;
        QFont m_buttonFont;
        QFont m_titleFont;
        QString m_title;
        QColor m_titleColor;
        QString m_message;
        QFont m_messageFont;

    public:
        MessageDialog(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        QColor buttonColor() const;
        QFont buttonFont() const;
        QFont titleFont() const;
        QString title() const;
        QColor titleColor() const;
        QString message() const;
        QFont messageFont() const;

    private Q_SLOTS:
        void repositionButton();
        void applyButtonFont(QFont font);
        void applyButtonColor(QColor color);

    public Q_SLOTS:
        void setButtonColor(QColor buttonColor);
        void setButtonFont(QFont buttonFont);
        void setTitleFont(QFont titleFont);
        void setTitle(QString title);
        void setTitleColor(QColor titleColor);
        void setMessage(QString message);
        void setMessageFont(QFont messageFont);

    Q_SIGNALS:
        void buttonColorChanged(QColor buttonColor);
        void buttonFontChanged(QFont buttonFont);
        void titleFontChanged(QFont titleFont);
        void titleChanged(QString title);
        void titleColorChanged(QColor titleColor);
        void messageChanged(QString message);
        void messageFontChanged(QFont messageFont);
};

#endif // MESSAGEDIALOG_H
