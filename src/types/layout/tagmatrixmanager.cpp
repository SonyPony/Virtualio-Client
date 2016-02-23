#include "tagmatrixmanager.h"
#include <QJsonObject>
#include <QMap>
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
    for(QString key: m_tagsInMatrix.keys())
        tagNames.insert(key, m_tagsInMatrix[key]->name());

    return tagNames;
}

QMap<QString, QJsonObject> TagMatrixManager::tags() const
{
    QMap<QString, QJsonObject> tags;
    QJsonObject info;

    for(const QString& name: m_tagsInMatrix.keys()) {
        const QPointer<CloneTag> tag = m_tagsInMatrix[name];

        info["name"] = tag->name();
        info["pin"] = tag->currentPinNumber();
        info["options"] = QJsonValue(QJsonObject::fromVariantMap(tag->options()));
    }

    return tags;
}

QStringList TagMatrixManager::tagNamesInRow(int row, ExtentedEnums::Direction tagOrientation) const
{
    int actualRow = row;
    if(tagOrientation == ExtentedEnums::Left)
        actualRow += 20;    // 20 is count of rows of dropgrid

    QRegularExpression re(QString("^\\d+\\/%1$").arg(actualRow));
    QStringList namesInRow;

    for(QString serializedPos: m_tagsInMatrix.keys()) {
        if(re.match(serializedPos).hasMatch())
            namesInRow.append(m_tagsInMatrix[serializedPos]->name());
    }

    return namesInRow;
}

void TagMatrixManager::reindexTag(QPoint newMatrixPos, DropableObject *dropObject)
{
    CloneTag* tag = (CloneTag*)dropObject;
    QPointer<CloneTag> cloneTag(tag);
    const QString key = m_tagsInMatrix.key(cloneTag);

    m_tagsInMatrix.remove(key);
    m_tagsInMatrix.insert(this->pointToString(newMatrixPos, tag->currentDirection()), cloneTag);
}

void TagMatrixManager::registerObject(CloneTag *tag)
{
    QPoint matrixPos = tag->matrixPosition();
    QPointer<CloneTag> tagPointer(tag);

    m_tagsInMatrix.insert(this->pointToString(matrixPos, tag->currentDirection()), tagPointer);

    connect(tag, &CloneTag::aligned, this, &TagMatrixManager::reindexTag);
    connect(tag, &CloneTag::deleteRequest, [this, tag]() {
        this->unregisterObject(tag);
    });
}

void TagMatrixManager::unregisterObject(CloneTag *tag)
{
    QPointer<CloneTag> cloneTag(tag);
    m_tagsInMatrix.remove(m_tagsInMatrix.key(cloneTag));

    disconnect(tag, &CloneTag::aligned, this, &TagMatrixManager::reindexTag);
}

