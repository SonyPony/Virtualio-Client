#ifndef ABSTRACTSYNTAXHIGHLIGHTERWRAPPER_H
#define ABSTRACTSYNTAXHIGHLIGHTERWRAPPER_H

#include <QObject>
#include <QQuickItem>
#include "syntaxhighlighter.h"

class AbstractSyntaxHighlighterWrapper : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QQuickItem* target READ target WRITE setTarget NOTIFY targetChanged)

    protected:
        QQuickItem* m_target;
        SyntaxHighlighter* m_syntaxHighlighter;

    public:
        AbstractSyntaxHighlighterWrapper(QObject *parent = 0);

        QQuickItem* target() const;

    public Q_SLOTS:
        void setTarget(QQuickItem* target);

    Q_SIGNALS:
        void targetChanged(QQuickItem* target);
};

#endif // ABSTRACTSYNTAXHIGHLIGHTERWRAPPER_H
