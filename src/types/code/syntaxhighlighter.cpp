#include "syntaxhighlighter.h"
#include <QRegularExpression>

QTextCharFormat KeywordHightlightRule::textFormat = QTextCharFormat();

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    this->hightlightKeywords(text);
    this->hightlightSingleLines(text);
    this->hightlightMultiLines(text);
}

SyntaxHighlighter::SyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent)
{
    m_target = NULL;

    connect(this, &SyntaxHighlighter::textDocumentChanged, this, &SyntaxHighlighter::setupNewTextDocument);
}

QQuickItem *SyntaxHighlighter::target() const
{
    return m_target;
}

void SyntaxHighlighter::setupNewTextDocument(QQuickTextDocument *qmlDocument)
{
    QTextDocument* document = qmlDocument->textDocument();
    this->setDocument(document);
}

void SyntaxHighlighter::hightlightSingleLines(const QString &text)
{
    // single line rules
    QRegularExpression matchPattern;
    QRegularExpressionMatch match;
    int cursor;
    int capturedStart, capturedLength;

    for(const HighlightRule& rule: m_highlightsRules) {
        cursor = 0;
        matchPattern = rule.matchPattern;

        do {
            match = matchPattern.match(text, cursor);

            capturedStart = match.capturedStart();
            capturedLength = match.capturedLength();

            // set text format
            this->setFormat(capturedStart, capturedLength, rule.textFormat);
            cursor = capturedStart + capturedLength;

        } while(matchPattern.match(text, cursor).hasMatch());
    }
}

void SyntaxHighlighter::hightlightKeywords(const QString &text)
{
    // keywords rules
    QRegularExpression matchPattern;
    QRegularExpressionMatch match;
    int cursor;
    int capturedStart, capturedLength;

    for(const KeywordHightlightRule& rule: m_keywordsRules) {
        cursor = 0;
        matchPattern = rule.keywordPattern;

        do {
            match = matchPattern.match(text, cursor);

            capturedStart = match.capturedStart();
            capturedLength = match.capturedLength();

            // do not highlight followed bracket
            if(rule.bracketCanFollow && match.capturedEnd() != -1) {
                matchPattern.setPattern(rule.keyword);
                match = matchPattern.match(text, cursor);
                capturedStart = match.capturedStart();
                capturedLength = match.capturedLength();
            }

            // set text format
            this->setFormat(capturedStart, capturedLength, KeywordHightlightRule::textFormat);
            cursor = capturedStart + capturedLength;

        } while(matchPattern.match(text, cursor).hasMatch());
    }
}

void SyntaxHighlighter::hightlightMultiLines(const QString &text)
{
    // multiline rule
    if(!m_hasMultilineRule)
        return;

    const QRegularExpression startPattern = m_multilineHighLightRule.startPattern;
    const QRegularExpression endPattern = m_multilineHighLightRule.endPattern;

    this->setCurrentBlockState(0);
    int startIndex = 0;
    int endIndex = 0;
    int commentLength = 0;

    if(this->previousBlockState() != 1)
        startIndex = startPattern.match(text).capturedStart();

    while(startIndex >= 0) {
        endIndex = endPattern.match(text, ((endIndex < 0) ?0 :endIndex)).capturedEnd();
        if(endIndex == -1) {
            commentLength = text.length() - startIndex;
            this->setCurrentBlockState(1);
        }
        else
            commentLength = (endIndex - startIndex);

        setFormat(startIndex, commentLength, m_multilineHighLightRule.textFormat);
        startIndex = startPattern.match(text, endIndex).capturedStart();
    }
}

void SyntaxHighlighter::addKeyword(QString keyword, bool bracketCanFollow)
{
    QString postfixPattern("($| )");
    QString prefixPattern("(^| )");

    if(bracketCanFollow) {
        prefixPattern = "(^| |\\(|\\))";
        postfixPattern = "($| |\\(|\\))";
    }

    KeywordHightlightRule rule;
    rule.keyword = keyword;
    rule.keywordPattern = QRegularExpression(keyword.prepend(prefixPattern).append(postfixPattern));
    rule.bracketCanFollow = bracketCanFollow;

    m_keywordsRules.append(rule);
}

void SyntaxHighlighter::addKeywords(QStringList keywords, bool bracketCanFollow)
{
    for(const QString& keyword: keywords)
        this->addKeyword(keyword, bracketCanFollow);
}

void SyntaxHighlighter::setKeywordsFormat(QTextCharFormat format)
{
    KeywordHightlightRule::textFormat = format;
}

void SyntaxHighlighter::setMultilineHightlightRule(QRegularExpression startPattern, QRegularExpression endPattern, QTextCharFormat format)
{
    m_hasMultilineRule = true;
    m_multilineHighLightRule = {format, startPattern, endPattern};
}

void SyntaxHighlighter::setMultilineHightlightRule(MultilineHighlightRule rule)
{
    m_hasMultilineRule = true;
    m_multilineHighLightRule = rule;
}

void SyntaxHighlighter::addHighlightRule(HighlightRule rule)
{
    m_highlightsRules.append(rule);
}

void SyntaxHighlighter::addHighlightRule(QRegularExpression pattern, QTextCharFormat format)
{
    m_highlightsRules.append({format, pattern});
}

void SyntaxHighlighter::setTarget(QQuickItem *target)
{
    if (m_target == target)
        return;

    m_target = target;

    QVariant vTextDocument = target->property("textDocument");
    if(vTextDocument.canConvert<QQuickTextDocument*>())
        Q_EMIT this->textDocumentChanged(vTextDocument.value<QQuickTextDocument*>());

    Q_EMIT this->targetChanged(target);
}

