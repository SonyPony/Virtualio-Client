#include "tagsselectionmanager.h"
#include <core.h>

TagsSelectionManager::TagsSelectionManager(QObject *parent) : QObject(parent)
{
    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, QSIGNAL(QSignalMapper, mapped, (int)), [this](int index) {
        for(int i = 0; i < m_tags.length(); i++) {
            m_tags[i]->setSelected(i == index);
        }
        Q_EMIT this->selected(m_tags[index]);
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

