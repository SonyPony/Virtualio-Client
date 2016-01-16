#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QQuickItem>
#include <QQuickTextDocument>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

struct HighlightRule {
    QTextCharFormat textFormat;
    QRegularExpression matchPattern;
};

struct MultilineHighlightRule {
    QTextCharFormat textFormat;
    QRegularExpression startPattern;
    QRegularExpression endPattern;
};

struct KeywordHightlightRule {
    static QTextCharFormat textFormat;
    QRegularExpression keywordPattern;
    QString keyword;
    bool bracketCanFollow;
};

class SyntaxHighlighter : public QSyntaxHighlighter
{
        Q_OBJECT
        Q_PROPERTY(QQuickItem* target READ target WRITE setTarget NOTIFY targetChanged)

    private:
        QVector<HighlightRule> m_highlightsRules;
        MultilineHighlightRule m_multilineHighLightRule;
        QVector<KeywordHightlightRule> m_keywordsRules;
        bool m_hasMultilineRule;
        QQuickItem* m_target;

    protected:
        virtual void highlightBlock(const QString& text);

    public:
        SyntaxHighlighter(QObject *parent = 0);

        QQuickItem* target() const;

    private Q_SLOTS:
        void setupNewTextDocument(QQuickTextDocument* qmlDocument);
        void hightlightSingleLines(const QString& text);
        void hightlightKeywords(const QString& text);
        void hightlightMultiLines(const QString& text);

    public Q_SLOTS:
        void addKeyword(QString keyword, bool bracketCanFollow = false);
        void addKeywords(QStringList keywords, bool bracketCanFollow = false);
        void setKeywordsFormat(QTextCharFormat format);
        void setMultilineHightlightRule(QRegularExpression startPattern, QRegularExpression endPattern, QTextCharFormat format);
        void setMultilineHightlightRule(MultilineHighlightRule rule);
        void addHighlightRule(HighlightRule rule);
        void addHighlightRule(QRegularExpression pattern, QTextCharFormat format);
        void setTarget(QQuickItem* target);

    Q_SIGNALS:
        void targetChanged(QQuickItem* target);
        void textDocumentChanged(QQuickTextDocument* document);
};

#endif // SYNTAXHIGHLIGHTER_H
