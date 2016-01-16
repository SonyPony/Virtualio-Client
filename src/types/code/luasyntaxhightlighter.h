#ifndef LUASYNTAXHIGHTLIGHTER_H
#define LUASYNTAXHIGHTLIGHTER_H

#include <QObject>
#include <QQuickItem>
#include "abstractsyntaxhighlighterwrapper.h"

class LuaSyntaxHightlighter : public AbstractSyntaxHighlighterWrapper
{
        Q_OBJECT

    public:
        LuaSyntaxHightlighter(QObject *parent = 0);
};

#endif // LUASYNTAXHIGHTLIGHTER_H
