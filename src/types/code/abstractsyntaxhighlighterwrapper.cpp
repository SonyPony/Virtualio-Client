#include "abstractsyntaxhighlighterwrapper.h"

AbstractSyntaxHighlighterWrapper::AbstractSyntaxHighlighterWrapper(QObject *parent): QObject(parent)
{
    m_target = NULL;
    m_syntaxHighlighter = new SyntaxHighlighter(this);
}

QQuickItem *AbstractSyntaxHighlighterWrapper::target() const
{
    return m_target;
}

void AbstractSyntaxHighlighterWrapper::setTarget(QQuickItem *target)
{
    if (m_target == target)
        return;

    m_target = target;
    emit targetChanged(target);
}

