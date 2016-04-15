#include "tagscontainer.h"
#include <types/cloneableobject/cloneabletag.h>
#include <QFont>

TagsContainer::TagsContainer(QQuickItem *parent): PaintedItem(parent)
{
    m_visibleTags = QStringList();
    m_widthAnimation = new QPropertyAnimation(this, "width", this);
    m_widthAnimation->setDuration(250);
    m_widthAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_body = new QQuickItem(this);
    m_body->setClip(true);

    m_settingsProvider = new TagSettingsProvider(QDir(QDir::currentPath() + "/settings"));

    connect(this, &TagsContainer::visibleTagsChanged, this, &TagsContainer::changeTagView);
    connect(this, &TagsContainer::widthChanged, [this]() {
        m_body->setWidth(this->width() - this->height());
    });
    connect(this, &TagsContainer::heightChanged, [this]() {
        m_body->setHeight(this->height());
    });
}

void TagsContainer::paint(QPainter *painter)
{
    const double triangleLen = this->height();
    const QPointF triangle[3] = {
        QPointF(this->width() - triangleLen, triangleLen),
        QPointF(this->width(), 0),
        QPointF(this->width() - triangleLen, 0)
    };

    painter->setPen(m_color);
    painter->setBrush(m_color);

    painter->drawRect(boundingRect().adjusted(0, 0, -triangleLen, 0));
    painter->drawConvexPolygon(triangle, 3);
    painter->setClipRect(painter->clipBoundingRect().adjusted(0, 0, -triangleLen, 0));
}

QColor TagsContainer::textColor() const
{
    return m_textColor;
}

QFont TagsContainer::font() const
{
    return m_font;
}

int TagsContainer::spacing() const
{
    return m_spacing;
}

QSize TagsContainer::tagSize() const
{
    return m_tagSize;
}

QStringList TagsContainer::visibleTags() const
{
    return m_visibleTags;
}

void TagsContainer::animateWidthChange(double width)
{
    m_widthAnimation->setCurrentTime(m_widthAnimation->duration());

    m_widthAnimation->setEndValue(width);
    m_widthAnimation->start();
}

void TagsContainer::showAndHideTags()
{
    for(QString tagName: m_tags.keys()) {
        if(m_visibleTags.contains(tagName)) {
            const int tagIndex = m_visibleTags.indexOf(tagName);

            m_tags[tagName]->fadeIn();
            m_tags[tagName]->setX(tagIndex * m_tagSize.width() + m_spacing * (tagIndex + 1));
        }

        else
            m_tags[tagName]->fadeOut();
    }
}

void TagsContainer::changeTagView(QStringList tags)
{
    this->showAndHideTags();
    this->animateWidthChange((m_tagSize.width() + spacing()) * tags.length() + this->height());
}

CloneableTag* TagsContainer::addTag(TagSettings settings)
{
    CloneableTag* cloneableTag = new CloneableTag(
        settings.name(),
        settings.tagStyle()["primaryColor"].toString(),
        settings.tagStyle()["secondaryColor"].toString(),
        settings.tagStyle()["focusColor"].toString(),
        ExtentedEnums::Right,
        m_body
    );

    cloneableTag->appearance()->setTextColor(m_textColor);
    cloneableTag->appearance()->setFont(m_font);

    cloneableTag->setParentItem(m_body);
    cloneableTag->setWidth(m_tagSize.width());
    cloneableTag->setHeight(m_tagSize.height());

    m_tags.insert(settings.name(), cloneableTag);

    connect(cloneableTag, &CloneableTag::newObject, this, &TagsContainer::newObject);
    connect(this, &TagsContainer::lock, cloneableTag, &CloneableTag::lock);
    connect(this, &TagsContainer::unlock, cloneableTag, &CloneableTag::unlock);

    return cloneableTag;
}

void TagsContainer::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    Q_EMIT textColorChanged(textColor);
}

void TagsContainer::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    Q_EMIT fontChanged(font);
}

void TagsContainer::createTags()
{
    CloneableTag *cloneableTag = NULL;
    QStringList names = m_settingsProvider->extractSettingsNames();
    const double vCenter = (this->height() - m_tagSize.height()) / 2.;

    for(QString name: names) {
        const int index = m_visibleTags.indexOf(name);

        cloneableTag = this->addTag(m_settingsProvider->tagSettings(name));
        cloneableTag->setX(index * m_tagSize.width() + m_spacing * (index + 1));
        cloneableTag->setY(vCenter);

        if(!m_visibleTags.contains(name))
            cloneableTag->fadeOut();
    }

    this->setWidth((m_tagSize.width() + spacing()) * names.length() + this->height());
}

void TagsContainer::setSpacing(int spacing)
{
    if (m_spacing == spacing)
        return;

    m_spacing = spacing;
    emit spacingChanged(spacing);
}

void TagsContainer::setTagSize(QSize tagSize)
{
    if (m_tagSize == tagSize)
        return;

    m_tagSize = tagSize;
    emit tagSizeChanged(tagSize);
}

void TagsContainer::setVisibleTags(QStringList visibleTags)
{
    if (m_visibleTags == visibleTags)
        return;

    m_visibleTags = visibleTags;
    emit visibleTagsChanged(visibleTags);
}

void TagsContainer::syntheticNewTag(QString type, QPoint droppointPos, QJsonObject settings)
{
    Q_ASSERT(m_tags.keys().contains(type));

    CloneTag* tag = m_tags[type]->createTag();
    tag->ungrabMouse();

    tag->setOptions(settings.toVariantMap());
    tag->setX(droppointPos.x());
    tag->setY(droppointPos.y());

    Q_EMIT tag->dropped(tag);
}

