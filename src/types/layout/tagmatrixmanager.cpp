#include "tagmatrixmanager.h"

#include <QRegularExpression>

QString TagMatrixManager::pointToString(QPoint point, ExtentedEnums::Direction tagOrientation) const
{
    // to differentiate current dropgrid
    int diff = 0;
    if(tagOrientation == ExtentedEnums::Left)
        diff += 20;     // 20 is count of rows of dropgrid

    return QString("%1/%2").arg(point.x()).arg(point.y() + diff);
}

TagMatrixManager::TagMatrixManager(QObject *parent) : QObject(parent)
{

}

QMap<QString, QString> TagMatrixManager::tagsNamesInMatrix() const
{
    QMap<QString, QString> tagNames;
    for(QString key: m_tagsNamesInMatrix.keys())
        tagNames.insert(key, m_tagsNamesInMatrix[key]->name());

    return tagNames;
}

QStringList TagMatrixManager::tagNamesInRow(int row, ExtentedEnums::Direction tagOrientation) const
{
    int actualRow = row;
    if(tagOrientation == ExtentedEnums::Left)
        actualRow += 20;    // 20 is count of rows of dropgrid

    QRegularExpression re(QString("\\d+\\/%1").arg(actualRow));
    QStringList namesInRow;

    for(QString serializedPos: m_tagsNamesInMatrix.keys()) {
        if(re.match(serializedPos).hasMatch())
            namesInRow.append(m_tagsNamesInMatrix[serializedPos]->name());
    }

    return namesInRow;
}

void TagMatrixManager::reindexTag(QPoint newMatrixPos, CloneTag *tag)
{
    QPointer<CloneTag> cloneTag(tag);

    const QString key = m_tagsNamesInMatrix.key(cloneTag);

    m_tagsNamesInMatrix.remove(key);
    m_tagsNamesInMatrix.insert(this->pointToString(newMatrixPos, tag->currentDirection()), cloneTag);
}

void TagMatrixManager::registerObject(CloneTag *tag)
{
    QPoint matrixPos = tag->matrixPosition();
    QPointer<CloneTag> tagPointer(tag);

    m_tagsNamesInMatrix.insert(this->pointToString(matrixPos, tag->currentDirection()), tagPointer);
    m_tagsInMatrix.append(QPointer<CloneTag>(tag));

    connect(tag, &CloneTag::matrixPositionChanged, this, &TagMatrixManager::reindexTag);
    connect(tag, &CloneTag::deleteRequest, [this, tag]() {
        this->unregisterObject(tag);
    });
}

void TagMatrixManager::unregisterObject(CloneTag *tag)
{
    QPointer<CloneTag> cloneTag(tag);
    m_tagsInMatrix.removeAll(cloneTag);
    m_tagsNamesInMatrix.remove(m_tagsNamesInMatrix.key(cloneTag));

    disconnect(tag, &CloneTag::matrixPositionChanged, this, &TagMatrixManager::reindexTag);
}

