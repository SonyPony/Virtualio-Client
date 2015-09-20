#include "clonetag.h"
#include <qmath.h>
#include "extentedmath.h"
#include "fraction.h"

CloneTag::CloneTag(int index, TagAppearance *appearance, QQuickItem *parent): CloneObject(index, parent)
{
    m_currentDirection = ExtentedEnums::Left;

    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_opacityAnimation->setDuration(250);

    setAcceptedMouseButtons(Qt::AllButtons);
    setParentItem(parent);
    setWidth(parent->width());
    setHeight(parent->height());

    m_tagAppearance = new TagAppearance(appearance, this);
    update(boundingRect().toRect());

    //need just height to resize
    connect(parent, SIGNAL(heightChanged()), this, SLOT(resize()));
    connect(m_tagAppearance, SIGNAL(requestUpdate()), this, SLOT(update()));
    connect(this, SIGNAL(currentPinNumberChanged(int)), this, SLOT(update()));
    connect(this, SIGNAL(matrixPositionChanged(QPoint)), this, SLOT(reemitMatrixPositionChanged(QPoint)));
}

void CloneTag::paint(QPainter *painter)
{
    m_tagAppearance->paintTag(painter);
    painter->setPen(QPen("white"));
    painter->setFont(QFont("Helvetica", 10));
    painter->drawText(m_tagAppearance->body(), QStringLiteral(" GPIO"), QTextOption(Qt::AlignCenter));
    //painter->drawText(boundingRect(), QString::number(m_currentPinNumber));
}

void CloneTag::reemitMatrixPositionChanged(QPoint position)
{
    emit matrixPositionChanged(position, this);
}

void CloneTag::resize()
{
    const double parentHeight = parentItem()->height();
    const double height = Fraction(parentHeight, 420) * 18;
    setSize(QSizeF(Fraction(80, 25) * height, height));
}

void CloneTag::setCurrentPinNumber(int pinNumber)
{
    if(m_currentPinNumber == pinNumber)
        return;

    m_currentPinNumber = pinNumber;
    emit currentPinNumberChanged(pinNumber);
}

void CloneTag::pointTo(ExtentedEnums::Direction direction)
{
    Q_ASSERT(direction == ExtentedEnums::Left || direction == ExtentedEnums::Right);

    if(m_currentDirection == direction)
        return;

    m_currentDirection = direction;
    m_tagAppearance->pointTo(direction);
}

void CloneTag::enteredIntoGrid()
{
    if(m_opacityAnimation->endValue() == 1)
        return;
    m_opacityAnimation->stop();
    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(1);
    m_opacityAnimation->start();
}

void CloneTag::leavedFromGrid()
{
    if(m_opacityAnimation->endValue() == 0.5)
        return;
    m_opacityAnimation->stop();
    m_opacityAnimation->setStartValue(opacity());
    m_opacityAnimation->setEndValue(0.5);
    m_opacityAnimation->start();
}


