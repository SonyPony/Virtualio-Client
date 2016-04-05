#include "tagabledil.h"
#include <QSvgRenderer>
#include <QJsonObject>
#include "fraction.h"
#include "core.h"
#include <QDebug>

TagableDIL::TagableDIL()
{
    // left dropGrid
    DropGrid* dropGrid = new DropGrid(this);
    dropGrid->setObjectsAlign(Qt::AlignRight);
    m_dropGrids.insert("left", dropGrid);

    // right drop grid
    dropGrid = new DropGrid(this);
    dropGrid->setObjectsAlign(Qt::AlignLeft);
    m_dropGrids.insert("right", dropGrid);

    m_dropGridsManager = new DropGridsManager(this);
    m_dropGridsManager->setObjectsParent((QQuickItem*)this);

    for(DropGrid* grid: m_dropGrids.values()) {
        grid->setColumns(4);
        grid->setRows(21);
        grid->setColor("lightGray");
        m_dropGridsManager->registerGrid(grid);
    }

    m_tagMatrixManager = new TagMatrixManager(this);
    m_tagSelectionManager = new TagsSelectionManager(this);
    m_DILRenderer = new QSvgRenderer(QStringLiteral(":/resources/images/DIL.svg"), this);
    this->setAcceptedMouseButtons(Qt::LeftButton);

    m_combinationWatcher = new TagStrictCombinationWatcher(this);
    const QList<QStringList> allowedCombinations = {
        { "UTX" },
        { "GND", "FUNW" },
        { "VDD", "FUNW" },
        { "GPO", "FUNW" },
        { "FUN", "FUNW" }
    };

    for(QStringList allowedCombination: allowedCombinations)
        m_combinationWatcher->addAllowedCombination(allowedCombination);

    connect(m_tagSelectionManager, &TagsSelectionManager::disselected, this, &TagableDIL::disselectedTag);
    connect(m_tagSelectionManager, &TagsSelectionManager::disselectedAll, this, &TagableDIL::disselected);
    connect(m_tagSelectionManager, &TagsSelectionManager::selected, [this](CloneTag* tag) {
        Q_EMIT this->selectedTag(tag->name(), tag);
    });
}

void TagableDIL::paint(QPainter *painter)
{
    const double DILSizeRatio = this->height() / (double)m_DILRenderer->defaultSize().height();

    QSizeF DILSize;
    DILSize.setHeight(this->height());
    DILSize.setWidth((double)m_DILRenderer->defaultSize().width() * DILSizeRatio);

    QPointF DILPos((this->width() - DILSize.width()) / 2., 0);

    // draw DIL
    m_DILRenderer->render(painter, QRectF(DILPos, DILSize));

    // resize dropGrids
    double gridY = 7. * DILSizeRatio;
    QSizeF gridsSize((this->width() - DILSize.width()) / 2., this->height() - 2. * gridY);

    for(DropGrid* grid: m_dropGrids.values()) {
        grid->setWidth(gridsSize.width());
        grid->setHeight(gridsSize.height());
        grid->setY(gridY);
    }
    m_dropGrids["right"]->setX(width() - gridsSize.width());
}

void TagableDIL::setTagPinNumber(QPoint matrixPos, CloneTag *object)
{
    if(matrixPos == QPoint(-1, -1))
        object->setCurrentPinNumber(-1);

    else if(m_dropGrids["left"]->objectInsideGrid(object)) {
        object->setCurrentPinNumber(matrixPos.y() + 1);
        object->pointTo(ExtentedEnums::Right);
    }

    else {
        object->setCurrentPinNumber(m_dropGrids["right"]->rows() - 1 - matrixPos.y() + 20);
        object->pointTo(ExtentedEnums::Left);
    }
}

void TagableDIL::checkValidTagCombinations(CloneTag* currentlyDroppedTag)
{
    QStringList combination = m_tagMatrixManager->tagNamesInRow(
        currentlyDroppedTag->matrixPosition().y(),
        currentlyDroppedTag->currentDirection()
    );

    if(!m_combinationWatcher->checkCombination(combination))
        m_dropGridsManager->unregisterObject(currentlyDroppedTag);
}

QStringList TagableDIL::objectNamesOfConcreteTagType(QString tagName)
{
    const QMap<QString, QJsonObject> tags = m_tagMatrixManager->tags();
    QStringList result;

    for(const QJsonObject& info: tags.values()) {
        if(info["name"] == tagName) {
            result.append(info["options"].toObject()["Object name"].toString());
        }
    }

    return result;
}

CloneTag* TagableDIL::tag(int pin, QString name) const
{
    QPointer<CloneTag> tag = m_tagMatrixManager->tag(pin, name);
    Q_ASSERT(!tag.isNull());
    return tag.data();
}

QJsonObject TagableDIL::selectedTagInfo()
{
    QJsonObject info;
    QPointer<CloneTag> tag = m_tagSelectionManager->lastSelectedTag();

    if(tag.isNull())
        return info;
    info.insert("pin", QJsonValue(tag->currentPinNumber()));
    info.insert("pinType", QJsonValue(tag->name()));
    info.insert("options", QJsonValue(QJsonObject::fromVariantMap(tag->options())));

    return info;
}

QJsonArray TagableDIL::tagsFunction()
{
    QJsonArray result;

    const QJsonArray tags = this->tags();
    static const QStringList digitalIn = { "GPI", "FUNW" };
    static const QStringList digitalOut = { "GPO", "GND", "VDD" };
    static const QStringList uartTX = { "UTX" };

    for(const QJsonValue vTag: tags) {
        QJsonObject tag = vTag.toObject();
        const QString tagType = tag["name"].toString();

        if(digitalIn.contains(tagType))
            tag["name"] = "DigitalIn";
        else if(digitalOut.contains(tagType))
            tag["name"] = "DigitalOut";
        else if(uartTX.contains(tagType))
            tag["name"] = "UARTTX";

        result.append(tag);
    }

    return result;
}

QJsonArray TagableDIL::tags()
{
    QJsonArray tags;
    const QMap<QString, QJsonObject> unformatedTags = m_tagMatrixManager->tags();

    for(const QJsonObject& singleTagInfo: unformatedTags.values())
        tags.append(QJsonValue(singleTagInfo));

    return tags;
}

void TagableDIL::clear()
{
    for(QPointer<CloneTag> tag: m_tagMatrixManager->pTags().values())
        m_dropGridsManager->unregisterObject(tag);
}

DropGrid* TagableDIL::dropGrid(QString side)
{
    Q_ASSERT(side == "left" || side == "right");
    return m_dropGrids[side];;
}

QPoint TagableDIL::dropPosition(int pinNumber)
{
    Q_ASSERT(pinNumber > 0 && pinNumber <= 40);

    if(pinNumber > 20) {
        return QPoint(
            m_dropGrids["right"]->x() + 2,
            m_dropGrids["right"]->horizontalGridLinesY()[40 - pinNumber]
        );
    }

    else {
        return QPoint(
            2,
            m_dropGrids["left"]->horizontalGridLinesY()[pinNumber]
        );
    }
}

void TagableDIL::registerTag(CloneTag *object)
{
    m_tagMatrixManager->registerObject(object);
    m_tagSelectionManager->registerTag(object);
    m_dropGridsManager->registerObject(object);
    connect(this, &TagableDIL::lockTags, object, &CloneTag::lock);
    connect(this, &TagableDIL::unlockTags, object, &CloneTag::unlock);
    connect(object, SIGNAL(matrixPositionChanged(QPoint,CloneTag*)), this, SLOT(setTagPinNumber(QPoint,CloneTag*)));
    connect(object, &CloneTag::dropped, [this, object]() {
        this->checkValidTagCombinations(object);
    });
}

void TagableDIL::disselectAll()
{
    m_tagSelectionManager->disselectAll();
}

void TagableDIL::serializeTags()
{
    m_tagMatrixManager->tags();
}

void TagableDIL::generateTags()
{

}












