#ifndef TAGSTRICTCOMBINATIONWATCHER_H
#define TAGSTRICTCOMBINATIONWATCHER_H

#include <QMap>
#include <QStringList>
#include <QObject>
#include <QSet>

class TagStrictCombinationWatcher : public QObject
{
        Q_OBJECT
    protected:
        QMap<QString, QSet<QString> > m_allowedCombinations;

    public:
        TagStrictCombinationWatcher(QObject *parent = 0);

        bool checkCombination(QStringList combination);

    public Q_SLOTS:
        void addAllowedCombination(QStringList combination);
};

#endif // TAGSTRICTCOMBINATIONWATCHER_H
