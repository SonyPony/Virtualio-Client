#include "tagsselectionmanager.h"
#include <core.h>

TagsSelectionManager::TagsSelectionManager(QObject *parent) : QObject(parent)
{
    m_lastSelectedTag = NULL;
    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, QSIGNAL(QSignalMapper, mapped, (int)), [this](int index) {
        if(m_lastSelectedTag != NULL)
            Q_EMIT this->disselected(m_lastSelectedTag);

        for(int i = 0; i < m_tags.length(); i++)
            m_tags[i]->setSelected(i == index);

        Q_EMIT this->selected(m_tags[index]);

        m_lastSelectedTag = m_tags[index];
    });
}

void TagsSelectionManager::registerTag(CloneTag *tag)
{
    connect(tag, SIGNAL(catched()), m_signalMapper, SLOT(map()));
    // m_tags.length() == index of tag now
    m_signalMapper->setMapping(tag, m_tags.length());
    m_tags.append(tag);
}

void TagsSelectionManager::unregisterTag(CloneTag *tag)
{
    disconnect(tag, SIGNAL(catched()), m_signalMapper, SLOT(map()));
    m_tags.removeAll(tag);
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

