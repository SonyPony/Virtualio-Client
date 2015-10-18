#include "clonetag.h"
#include <qmath.h>
#include "extentedmath.h"
#include "fraction.h"

CloneTag::CloneTag(int index, TagAppearance *appearance, QQuickItem *parent): CloneObject(index, parent)
{
    m_currentDirection = ExtentedEnums::Left;

    m_tagPinView = new TagPinView(this);
    m_tagPinView->setColor("#303031");
    m_tagPinView->setTextColor("white");

    //m_moveAnimation = new MoveAnimation(m_tagPinView, 250, this);
    //m_moveAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_opacityAnimation->setDuration(150);

    m_pinViewMoveAnimation = new QPropertyAnimation(m_tagPinView, "x", this);
    m_pinViewMoveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_pinViewMoveAnimation->setDuration(250);

    m_opacityAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_opacityAnimation->setDuration(250);

    setAcceptedMouseButtons(Qt::AllButtons);
    setParentItem(parent);
    setWidth(parent->width() + parent->height());
    setHeight(parent->height());

    m_tagAppearance = new TagAppearance(appearance, this);
    m_tagPinView->setSize(QSizeF(height(), height()));
    update(boundingRect().toRect());

    //need just height to resize
    connect(parent, SIGNAL(heightChanged()), this, SLOT(resize()));
    connect(m_tagAppearance, SIGNAL(requestUpdate()), this, SLOT(update()));
    connect(this, SIGNAL(currentPinNumberChanged(int)), this, SLOT(update()));
    connect(this, SIGNAL(matrixPositionChanged(QPoint)), this, SLOT(reemitMatrixPositionChanged(QPoint)));
    connect(this, SIGNAL(catched()), this, SLOT(showPinView()));
    connect(this, SIGNAL(dropped(DropableObject*)), this, SLOT(hidePinView()));
    connect(m_tagPinView, SIGNAL(xChanged()), this, SLOT(update()));
    connect(this, SIGNAL(directionChanged()), this, SLOT(repostionPinView()));
}

void CloneTag::paint(QPainter *painter)
{
    m_tagPinView->paintPinView(painter);
    m_tagAppearance->paintTag(painter);
    painter->setPen(QPen("white"));
    painter->setFont(QFont("Helvetica", 10));
    painter->drawText(m_tagAppearance->body(), QStringLiteral(" GPIO"), QTextOption(Qt::AlignCenter));
    painter->setPen(QPen("lime"));
    painter->setBrush(QBrush("transparent"));
    painter->drawRect(boundingRect().adjusted(0, 0, -1, -1));
}

void CloneTag::repostionPinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());

    if(m_currentDirection == ExtentedEnums::Left)
        m_pinViewMoveAnimation->setEndValue(width() - height());

    else
        m_pinViewMoveAnimation->setEndValue(0);

    m_pinViewMoveAnimation->start();
}

void CloneTag::showPinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());

    if(m_currentDirection == ExtentedEnums::Right)
        m_pinViewMoveAnimation->setEndValue(0);

    else
        m_pinViewMoveAnimation->setEndValue(width() - height());

    m_pinViewMoveAnimation->start();
}

void CloneTag::hidePinView()
{
    m_pinViewMoveAnimation->setStartValue(m_tagPinView->x());

    if(m_currentDirection == ExtentedEnums::Right)
        m_pinViewMoveAnimation->setEndValue(height());

    else
        m_pinViewMoveAnimation->setEndValue(width() - 2 * height() - 1);

    m_pinViewMoveAnimation->start();
}

void CloneTag::repositionBody(ExtentedEnums::Direction direction)
{
    if(m_currentDirection == ExtentedEnums::Right)
        m_tagAppearance->setX(height());
    else
        m_tagAppearance->setX(0);
    qDebug() << "X: " << m_tagAppearance->x();
}

void CloneTag::reemitMatrixPositionChanged(QPoint position)
{
    emit matrixPositionChanged(position, this);
}

void CloneTag::resize()
{
    const double parentHeight = parentItem()->height();
    const double height = Fraction(parentHeight, 420) * 18;
    setSize(QSizeF(Fraction(80, 25) * height + height, height));
    m_tagPinView->setSize(QSizeF(height, height));
    m_tagAppearance->setSize(QSizeF(width() - height, height));

    //repostionPinView();
    repositionBody(m_currentDirection);
}

void CloneTag::setCurrentPinNumber(int pinNumber)
{
    if(m_currentPinNumber == pinNumber)
        return;

    m_currentPinNumber = pinNumber;
    m_tagPinView->setPinNumber(m_currentPinNumber);
    emit currentPinNumberChanged(pinNumber);
}

void CloneTag::pointTo(ExtentedEnums::Direction direction)
{
    Q_ASSERT(direction == ExtentedEnums::Left || direction == ExtentedEnums::Right);

    if(m_currentDirection == direction)
        return;

    m_currentDirection = direction;
    repositionBody(direction);
    m_tagAppearance->pointTo(direction);

    emit directionChanged();
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


