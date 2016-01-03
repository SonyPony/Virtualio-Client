#include "tagabledil.h"
#include <QSvgRenderer>
#include "fraction.h"
#include "core.h"

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

    m_tagSelectionManager = new TagsSelectionManager(this);
    m_DILRenderer = new QSvgRenderer(QStringLiteral(":/resources/images/DIL.svg"), this);

    connect(m_tagSelectionManager, &TagsSelectionManager::selected, [this](CloneTag* tag) {
        Q_EMIT this->selected(tag->appearance()->name(), tag->options());
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

DropGrid* TagableDIL::dropGrid(QString side)
{
    Q_ASSERT(side == "left" || side == "right");
    return m_dropGrids[side];;
}

void TagableDIL::registerTag(CloneTag *object)
{
    m_tagSelectionManager->registerTag(object);
    m_dropGridsManager->registerObject(object);
    connect(object, SIGNAL(matrixPositionChanged(QPoint,CloneTag*)), this, SLOT(setTagPinNumber(QPoint,CloneTag*)));
}

