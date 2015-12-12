#include "tagappearance.h"
#include "extentedmath.h"
#include <qmath.h>

TagAppearance::TagAppearance(QColor firstColor, QColor secondColor, ExtentedEnums::Direction direction, QQuickItem *parent): QQuickPaintedItem(parent)
{
    m_firstColor = firstColor;
    m_secondColor = secondColor;
    m_currentDirection = direction;

    m_bodyMoveAnimation = new QPropertyAnimation(this, "bodyPosition", this);
    m_bodyMoveAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuad));
    m_bodyMoveAnimation->setDuration(250);

    setParentItem(parent);
    setBodySize();

    connect(this, &TagAppearance::xChanged, [this]() {
        setBodyPosition();
    });

    connect(this, &QQuickItem::widthChanged, this, &TagAppearance::setBodySize);
    connect(this, &QQuickItem::heightChanged, this, &TagAppearance::setBodySize);
    connect(this, SIGNAL(bodyPositionChanged(QPoint)), this, SLOT(updatePaintTag()));
}

TagAppearance::TagAppearance(TagAppearance *other, QQuickItem *parent): TagAppearance(other->firstColor(), other->secondColor(), other->currentDirection(), parent)
{
    this->setWidth(other->width());
    this->setHeight(other->height());
    m_currentDirection = other->currentDirection();

    connect(other, &QQuickItem::widthChanged, [this, other]() {
        this->setWidth(other->width());
    });

    connect(other, &QQuickItem::heightChanged, [this, other]() {
        this->setHeight(other->height());
    });
}

void TagAppearance::paintTag(QPainter *painter)
{
    if(!height() || !width())
        return;

    setBodyPosition();
    const double triangleWidth = round(ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8));
    const int x = round(this->x());
    QPoint leftTriangle[3] = {
        QPoint(x + triangleWidth, 0),
        QPoint(x, height() / 2.),
        QPoint(x + triangleWidth, height())
    };

    QPoint rightTriangle[3] = {
        QPoint(width() + x - triangleWidth - 1, 0),
        QPoint(width() + x, height() / 2.),
        QPoint(width() + x - triangleWidth - 1, height())
    };

    QLineF diagonal = ExtentedMath::rectDiagonal(QRect(x, y(), m_body.width(), m_body.height()));
    double diagonalLength = ExtentedMath::lineLength(diagonal);
    double alpha = qAtan2(height(), m_body.width());
    double c = (diagonalLength / 2.) / qCos(alpha);

    QLinearGradient fillPattern(m_body.width() - c + x, 0, c + x, height());

    if(m_currentDirection == ExtentedEnums::Left) { //move gradient as well
        fillPattern.setStart(fillPattern.start() + QPointF(triangleWidth, 0));
        fillPattern.setFinalStop(fillPattern.finalStop() + QPointF(triangleWidth, 0));
    }

    //fill pairs
    /*
     * QColor(0, 162, 232), QColor(0, 145, 206) - BLUE
     * #E6063C, #C40002 - RED
     * QColor(255, 201, 14), QColor(255, 152, 38) - BEIGE
     * QColor(62, 62, 62), QColor(42, 42, 42) - GRAY
     */
    /*fillPattern.setColorAt(0.49, QColor(186, 224, 31)); //light
    fillPattern.setColorAt(0.5, QColor(111, 196, 34));  //dark*/
    fillPattern.setColorAt(0.49, m_firstColor); //light
    fillPattern.setColorAt(0.5, m_secondColor);  //dark

    painter->setPen(QPen("transparent"));
    painter->setBrush(QBrush(fillPattern));
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawConvexPolygon(leftTriangle, 3);
    painter->drawConvexPolygon(rightTriangle, 3);
    painter->drawRect(m_body);
}

QRectF TagAppearance::body() const
{
    return m_body;
}

void TagAppearance::pointTo(ExtentedEnums::Direction direction)
{
    Q_ASSERT(direction == ExtentedEnums::Left || direction == ExtentedEnums::Right);

    if(m_currentDirection == direction)
        return;

    m_currentDirection = direction;

    if(direction == ExtentedEnums::Right) {
        m_bodyMoveAnimation->setStartValue(QPoint(m_body.x()+ x(), m_body.y()));
        m_bodyMoveAnimation->setEndValue(QPoint(x(), 0));
    }
    else {
        m_bodyMoveAnimation->setStartValue(QPoint(0, m_body.y()));
        m_bodyMoveAnimation->setEndValue(QPoint(width() - m_body.width(), m_body.y()));
    }
    m_bodyMoveAnimation->start();
}

void TagAppearance::setBodySize()
{
    if(!height() || !width())
        return;

    double triangleWidth = round(ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8));
    m_body.setWidth(width() - triangleWidth);
    m_body.setHeight(height());

    updatePaintTag();
}

void TagAppearance::updatePaintTag()
{
    emit requestUpdate();
}

void TagAppearance::setBodyPosition()
{
    if(!height())
        return;

    const double triangleWidth = round(ExtentedMath::legOfRightTriangle(height() / 2., height() * 0.8));
    if(m_currentDirection == ExtentedEnums::Right)
        m_body.moveTo(x(), 0);
    else
        m_body.moveTo(x() + triangleWidth, 0);
}

QPoint TagAppearance::bodyPosition() const
{
    return m_bodyPosition;
}

QColor TagAppearance::firstColor() const
{
    return m_firstColor;
}

QColor TagAppearance::secondColor() const
{
    return m_secondColor;
}

ExtentedEnums::Direction TagAppearance::currentDirection() const
{
    return m_currentDirection;
}

void TagAppearance::setBodyPosition(QPoint bodyPosition)
{
    if (m_bodyPosition == bodyPosition)
        return;

    m_bodyPosition = bodyPosition;
    m_body.moveTo(bodyPosition);
    emit bodyPositionChanged(bodyPosition);
}
