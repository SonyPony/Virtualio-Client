#ifndef CLICKABLETEXT_H
#define CLICKABLETEXT_H

#include "textbutton.h"
#include <QPainter>
#include <QPropertyAnimation>

class ClickableText : public TextButton
{
        Q_OBJECT
        Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
        Q_PROPERTY(QColor descriptionColor READ descriptionColor WRITE setDescriptionColor NOTIFY descriptionColorChanged)
        Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
        Q_PROPERTY(QColor _backgroundColor READ _backgroundColor WRITE set_backgroundColor NOTIFY _backgroundColorChanged)
        Q_PROPERTY(int margins READ margins WRITE setMargins NOTIFY marginsChanged)
        Q_PROPERTY(bool showDescription READ showDescription WRITE setShowDescription NOTIFY showDescriptionChanged)

    private:
        QString m_description;
        QColor m_descriptionColor;
        QColor m_backgroundColor;
        QPropertyAnimation* m_backgroundAnimation;
        int m_margins;
        bool m_showDescription;
        // need to animate background color without changing it
        QColor p_backgroundColor;

    public:
        ClickableText(QQuickItem* parent = 0);
        ~ClickableText();

        virtual void paint(QPainter* painter);

        QString description() const;
        QColor descriptionColor() const;
        QColor backgroundColor() const;
        QColor _backgroundColor() const;
        int margins() const;
        bool showDescription() const;

    private Q_SLOTS:
        void hideBackground();
        void showBackGround();
        void resizeAccordingText();

    public Q_SLOTS:
        void setDescription(QString description);
        void setDescriptionColor(QColor descriptionColor);
        void setBackgroundColor(QColor backgroundColor);
        void set_backgroundColor(QColor _backgroundColor);
        void setMargins(int margins);
        void setShowDescription(bool showDescription);

    Q_SIGNALS:
        void descriptionChanged(QString description);
        void descriptionColorChanged(QColor descriptionColor);
        void backgroundColorChanged(QColor backgroundColor);
        void _backgroundColorChanged(QColor _backgroundColor);
        void marginsChanged(int margins);
        void showDescriptionChanged(bool showDescription);
};

#endif // CLICKABLETEXT_H
