#include "tagabledil.h"
#include <QSvgRenderer>
#include "../../core/fraction.h"
#include "../../core/core.h"

TagableDIL::TagableDIL()
{
    //left dropGrid
    DropGrid* dropGrid = new DropGrid(this);
    dropGrid->setObjectsAlign(Qt::AlignRight);
    m_dropGrids.insert("left", dropGrid);

    //right drop grid
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

    m_DILRenderer = new QSvgRenderer(QStringLiteral(":/resources/images/DIL.svg"), this);
}

void TagableDIL::paint(QPainter *painter)
{
    QSize DILSize = QSize(
                    Fraction(154, 714) * width(),
                    Fraction(406, 420) * height()
                );
    QPoint DILPos = QPoint(
                    Fraction(280, 714) * width(),
                    Fraction(7, 420) * height()
                );

    //draw DIL
    m_DILRenderer->render(painter, QRectF(DILPos, DILSize));

    //draw border for debug
    //painter->setPen(QPen("red"));
    //painter->setBrush(QBrush("transparent"));
    //painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));

    //resize dropGrids
    QSize gridsSize(Fraction(300, 714) * width(), height());

    for(DropGrid* grid: m_dropGrids.values()) {
        grid->setWidth(gridsSize.width());
        grid->setHeight(gridsSize.height());
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
    m_dropGridsManager->registerObject(object);
    connect(object, SIGNAL(matrixPositionChanged(QPoint,CloneTag*)), this, SLOT(setTagPinNumber(QPoint,CloneTag*)));
}

