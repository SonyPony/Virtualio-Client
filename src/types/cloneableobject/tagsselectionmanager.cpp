#include "tagsselectionmanager.h"
#include <core.h>

TagsSelectionManager::TagsSelectionManager(QObject *parent) : QObject(parent)
{
    m_selectedIndex = -1;
    m_lastSelectedTag = NULL;
    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, QSIGNAL(QSignalMapper, mapped, (int)), this, &TagsSelectionManager::handleTagSelection);
}

void TagsSelectionManager::handleTagSelection(int index)
{
    CloneTag* selectedTag = m_tags[index];
    this->removeGarbage();

    index = m_tags.indexOf(selectedTag);

    if(m_lastSelectedTag != NULL)
        Q_EMIT this->disselected(m_lastSelectedTag);

    for(QPointer<CloneTag> tag: m_tags) {
        if(!tag.isNull()) {
            m_selectedIndex = m_tags.indexOf(tag);
            tag->setSelected(m_selectedIndex == index);
        }
    }

    Q_EMIT this->selected(selectedTag);
    m_lastSelectedTag = selectedTag;
}

void TagsSelectionManager::removeGarbage()
{
    this->unregisterTag(NULL);
}

void TagsSelectionManager::remapTags()
{
    for(CloneTag* tag: m_tags)
        m_signalMapper->setMapping(tag, m_tags.indexOf(tag));
}

void TagsSelectionManager::handleSelectedTagDestruction()
{
    if(m_selectedIndex > -1)
        Q_EMIT this->disselectAll();
}

void TagsSelectionManager::registerTag(CloneTag *tag)
{
    connect(tag, SIGNAL(catched()), m_signalMapper, SLOT(map()));
    connect(tag, &CloneTag::deleteRequest, this, &TagsSelectionManager::handleSelectedTagDestruction);
    // m_tags.length() == index of tag now
    m_signalMapper->setMapping(tag, m_tags.length());
    m_tags.append(tag);
}

void TagsSelectionManager::unregisterTag(CloneTag *tag)
{
    m_tags.removeAll(tag);
    this->remapTags();
}

void TagsSelectionManager::disselectAll()
{
    if(m_lastSelectedTag == NULL)
        return;

    m_lastSelectedTag->setSelected(false);
    Q_EMIT this->disselected(m_lastSelectedTag);
    m_lastSelectedTag = NULL;

    Q_EMIT this->disselectedAll();
}

