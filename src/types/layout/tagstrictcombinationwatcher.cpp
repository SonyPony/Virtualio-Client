#include "tagstrictcombinationwatcher.h"

TagStrictCombinationWatcher::TagStrictCombinationWatcher(QObject *parent) : QObject(parent)
{
}

bool TagStrictCombinationWatcher::checkCombination(QStringList combination)
{
    combination.sort();
    QSet<QString> combinationSet = combination.toSet();
    // not a combination
    if(combinationSet.count() != combination.length())
        return false;

    QSet<QString> combinationsIntersect;

    for(QSet<QString> allowedCombination: m_allowedCombinations.values()) {
        combinationsIntersect = allowedCombination.intersect(combinationSet);

        if(combinationsIntersect.count() == combination.length())
            return true;
    }

    return false;
}

void TagStrictCombinationWatcher::addAllowedCombination(QStringList combination)
{
    combination.sort();

    const QString key = combination.join("");
    m_allowedCombinations[key] = combination.toSet();
}

