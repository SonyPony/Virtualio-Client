#ifndef HIDEABLEWIDGET_H
#define HIDEABLEWIDGET_H

#include <QQuickItem>
#include "painteditem.h"
#include <QPropertyAnimation>

class HideableWidget : public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(qreal titleFrameHeight READ titleFrameHeight WRITE setTitleFrameHeight NOTIFY titleFrameHeightChanged)
        Q_PROPERTY(qreal contentFrameHeight READ contentFrameHeight WRITE setContentFrameHeight NOTIFY contentFrameHeightChanged)
        Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
        Q_PROPERTY(QColor titleTextColor READ titleTextColor WRITE setTitleTextColor NOTIFY titleTextColorChanged)
        Q_PROPERTY(QFont titleFont READ titleFont WRITE setTitleFont NOTIFY titleFontChanged)
        Q_PROPERTY(QFont contentFont READ contentFont WRITE setContentFont NOTIFY contentFontChanged)
        Q_PROPERTY(QColor contentColor READ contentColor WRITE setContentColor NOTIFY contentColorChanged)
        Q_PROPERTY(int containerWidth READ containerWidth NOTIFY containerWidthChanged)
        Q_PROPERTY(int containerHeight READ containerHeight NOTIFY containerHeightChanged)
        Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

    private:
        QPropertyAnimation* m_resizeAnimation;
        QQuickItem* m_container;
        int m_containerWidth;
        int m_containerHeight;

    protected:
        qreal m_titleFrameHeight;
        qreal m_contentFrameHeight;
        QColor m_titleColor;
        QColor m_titleTextColor;
        QFont m_titleFont;
        QFont m_contentFont;
        QColor m_contentColor;
        QString m_title;
        bool m_hidden;

        virtual void mousePressEvent(QMouseEvent* e);

    public:
        HideableWidget(QQuickItem* parent = 0);

        virtual void paint(QPainter* painter);

        qreal titleFrameHeight() const;
        qreal contentFrameHeight() const;
        QColor titleColor() const;
        QColor titleTextColor() const;
        QFont titleFont() const;
        QFont contentFont() const;
        QColor contentColor() const;
        QQuickItem* container();
        int containerWidth() const;
        int containerHeight() const;
        QString title() const;

    private Q_SLOTS:
        void resize();
        void setContainerWidth(int containerWidth);
        void setContainerHeight(int containerHeight);

    public Q_SLOTS:
        void hide();
        void show();
        void unbindRepositioningContainer();
        void setContainerParent(QQuickItem* parent);

        void setTitleFrameHeight(qreal titleFrameHeight);
        void setContentFrameHeight(qreal contentFrameHeight);
        void setTitleColor(QColor titleColor);
        void setTitleTextColor(QColor titleTextColor);
        void setTitleFont(QFont titleFont);
        void setContentFont(QFont contentFont);
        void setContentColor(QColor contentColor);
        void setTitle(QString title);

    Q_SIGNALS:
        void titleFrameHeightChanged(qreal titleFrameHeight);
        void contentFrameHeightChanged(qreal contentFrameHeight);
        void titleColorChanged(QColor titleColor);
        void titleTextColorChanged(QColor titleTextColor);
        void titleFontChanged(QFont titleFont);
        void contentFontChanged(QFont contentFont);
        void contentColorChanged(QColor contentColor);
        void containerWidthChanged(int containerWidth);
        void containerHeightChanged(int containerHeight);
        void titleChanged(QString title);
};

#endif // HIDEABLEWIDGET_H
