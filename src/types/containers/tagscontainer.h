#ifndef TAGSCONTAINER_H
#define TAGSCONTAINER_H

#include <QJsonObject>
#include <QObject>
#include <QPainter>
#include <painteditem.h>
#include <types/cloneableobject/cloneabletag.h>
#include <types/settings/tagsettings.h>
#include <types/settings/tagsettingsprovider.h>
#include "tab.h"

class TagsContainer: public PaintedItem
{
        Q_OBJECT
        Q_PROPERTY(QSize tagSize READ tagSize WRITE setTagSize NOTIFY tagSizeChanged)
        Q_PROPERTY(int spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)
        Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
        Q_PROPERTY(QStringList visibleTags READ visibleTags WRITE setVisibleTags NOTIFY visibleTagsChanged)

    private:
        TagSettingsProvider* m_settingsProvider;
        QColor m_textColor;
        QFont m_font;
        int m_spacing;
        QSize m_tagSize;
        QStringList m_visibleTags;
        QMap<QString, CloneableTag*> m_tags;
        QPropertyAnimation* m_widthAnimation;
        QQuickItem* m_body;

    public:
        TagsContainer(QQuickItem *parent = 0);

        virtual void paint(QPainter* painter);

        QColor textColor() const;
        QFont font() const;
        int spacing() const;
        QSize tagSize() const;
        QStringList visibleTags() const;

    private Q_SLOTS:
        void animateWidthChange(double width);
        void showAndHideTags();

    public Q_SLOTS:
        void changeTagView(QStringList tags);
        CloneableTag *addTag(TagSettings settings);
        void setTextColor(QColor textColor);
        void setFont(QFont font);
        void createTags();
        void setSpacing(int spacing);
        void setTagSize(QSize tagSize);
        void setVisibleTags(QStringList visibleTags);
        void syntheticNewTag(QString type, QPoint droppointPos, QJsonObject settings);

    Q_SIGNALS:
        void lock();
        void unlock();
        void textColorChanged(QColor textColor);
        void fontChanged(QFont font);
        void spacingChanged(int spacing);
        void tagSizeChanged(QSize tagSize);
        void visibleTagsChanged(QStringList visibleTags);
        void newObject(CloneTag* object);
};

#endif // TAGSCONTAINER_H
