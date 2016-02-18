#include "pysyntaxhighlighter.h"

PySyntaxHighlighter::PySyntaxHighlighter(QObject *parent): AbstractSyntaxHighlighterWrapper(parent)
{
    // keyword format
    QTextCharFormat keywordformat;
    keywordformat.setForeground(QColor("orange"));
    const QStringList keywordsWithAllowedBrackets = {
        "False", "None", "True", "and", "as", "assert", "break", "class", "continue",
        "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if",
        "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return",
        "try", "while", "with", "yield"
    };

    m_syntaxHighlighter->addKeywords(keywordsWithAllowedBrackets, true);
    m_syntaxHighlighter->setKeywordsFormat(keywordformat);

    // singleline comment
    QTextCharFormat singlelineFormat;
    singlelineFormat.setForeground(QColor("green"));
    m_syntaxHighlighter->addHighlightRule(QRegularExpression("#.*"), singlelineFormat);

    // multiline comment
    QTextCharFormat multilineCommentFormat;
    multilineCommentFormat.setForeground(QColor("lightGray"));
    m_syntaxHighlighter->setMultilineHightlightRule(
        QRegularExpression("\"\"\""),
        QRegularExpression("\"\"\""),
        multilineCommentFormat
    );

    connect(this, &PySyntaxHighlighter::targetChanged, m_syntaxHighlighter, &SyntaxHighlighter::setTarget);
}

