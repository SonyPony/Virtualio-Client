#ifndef PYSYNTAXHIGHLIGHTER_H
#define PYSYNTAXHIGHLIGHTER_H

#include <QObject>
#include "abstractsyntaxhighlighterwrapper.h"

class PySyntaxHighlighter : public AbstractSyntaxHighlighterWrapper
{
        Q_OBJECT
    public:
        PySyntaxHighlighter(QObject* parent = 0);
};

#endif // PYSYNTAXHIGHLIGHTER_H
