#include "luasyntaxhightlighter.h"

LuaSyntaxHightlighter::LuaSyntaxHightlighter(QObject *parent) : AbstractSyntaxHighlighterWrapper(parent)
{
    //m_target = NULL;
    //m_syntaxHighlighter = new SyntaxHighlighter(this);

    // keyword format
    QTextCharFormat keywordformat;
    keywordformat.setForeground(QColor("orange"));
    const QStringList keywordsWithAllowedBrackets = {
        "break", "do", "end", "else", "elseif", "function", "if",
        "local", "nil", "not", "or", "repeat", "return", "then",
        "until", "while"
    };

    m_syntaxHighlighter->addKeywords(keywordsWithAllowedBrackets, true);
    m_syntaxHighlighter->setKeywordsFormat(keywordformat);

    // singleline comment
    QTextCharFormat singlelineFormat;
    singlelineFormat.setForeground(QColor("green"));
    m_syntaxHighlighter->addHighlightRule(QRegularExpression("--.*"), singlelineFormat);

    // multiline comment
    QTextCharFormat multilineCommentFormat;
    multilineCommentFormat.setForeground(QColor("lightGray"));
    m_syntaxHighlighter->setMultilineHightlightRule(
        QRegularExpression("--\\[\\["),
        QRegularExpression("\\]\\]"),
        multilineCommentFormat
    );

    connect(this, &LuaSyntaxHightlighter::targetChanged, m_syntaxHighlighter, &SyntaxHighlighter::setTarget);
}

